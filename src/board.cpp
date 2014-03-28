#include <cassert>
#include <fstream>
#include <iostream>

#include "controlcalculator.h"
#include "board.h"
#include "move.h"

namespace cengine
{
	Board::Board()
	{
		// Place white pieces
		pieces[WHITE_PAWNS] 	= 0xFF00;
		pieces[WHITE_ROOKS] 	= 0x81;
		pieces[WHITE_KNIGHTS]	= 0x42;
		pieces[WHITE_BISHOPS]	= 0x24;
		pieces[WHITE_QUEEN]		= 0x8;
		pieces[WHITE_KING]		= 0x10;

		// Place BLACK pieces by shifting the WHITE ones
		pieces[BLACK_PAWNS]		= pieces[WHITE_PAWNS] << 40;
		pieces[BLACK_ROOKS]		= pieces[WHITE_ROOKS] << 56;
		pieces[BLACK_KNIGHTS]	= pieces[WHITE_KNIGHTS] << 56;
		pieces[BLACK_BISHOPS]	= pieces[WHITE_BISHOPS] << 56;
		pieces[BLACK_QUEEN]		= pieces[WHITE_QUEEN] << 56;
		pieces[BLACK_KING]		= pieces[WHITE_KING] << 56;

		pieces[ALL_WHITE_PIECES] = 0;
		pieces[ALL_BLACK_PIECES] = 0;

		for (int i = WHITE_PAWNS; i <= WHITE_KING; i++) {
			pieces[ALL_WHITE_PIECES] |= pieces[i];
		}
		for (int i = BLACK_PAWNS; i <= BLACK_KING; i++) {
			pieces[ALL_BLACK_PIECES] |= pieces[i];
		}

		black_long_castling_available = true;
		black_short_castling_available = true;
		white_long_castling_available = true;
		white_short_castling_available = true;
		piece_taken = false;
		whites_turn = true;

		last_move = NULL;

		update_board_control();
	}

	Board::Board(const Board& board)
	{
		for (unsigned int i = WHITE_PAWNS; i < PIECES_SIZE; i++)
		{
			pieces[i] = board.pieces[i];
		}

		black_long_castling_available = board.is_black_long_castling_available();
		black_short_castling_available = board.is_black_short_castling_available();
		white_long_castling_available = board.is_white_long_castling_available();
		white_short_castling_available = board.is_white_short_castling_available();
		piece_taken = board.piece_taken;
		whites_turn = board.whites_turn;
		white_control = board.white_control;
		black_control = board.black_control;

		for (size_t i = 0; i < board.previous_moves.size(); i++) {
			previous_moves.push_back(new Move(*board.previous_moves[i]));
		}

		if (board.last_move != NULL) {
			last_move = new Move(*board.last_move);
		} else {
			last_move = NULL;
		}
	}

	Board::~Board()
	{
		if (last_move != NULL) {
			delete last_move;
		}
		if (!previous_moves.empty()) {
			for (size_t i = 0; i < previous_moves.size(); i++) {
				delete previous_moves[i];
				previous_moves[i] = NULL;
			}
			previous_moves.clear();
		}
	}

	Board& Board::operator=(const Board& board)
	{
		for (unsigned int i = WHITE_PAWNS; i < PIECES_SIZE; i++)
		{
			pieces[i] = board.pieces[i];
		}

		black_long_castling_available = board.is_black_long_castling_available();
		black_short_castling_available = board.is_black_short_castling_available();
		white_long_castling_available = board.is_white_long_castling_available();
		white_short_castling_available = board.is_white_short_castling_available();
		piece_taken = board.piece_taken;
		whites_turn = board.is_whites_turn();
		white_control = board.white_control;
		black_control = board.black_control;


		if (!previous_moves.empty()) {
			for (size_t i = 0; i < previous_moves.size(); i++) {
				delete previous_moves[i];
				previous_moves[i] = NULL;
			}
			previous_moves.clear();
		}
		for (size_t i = 0; i < board.previous_moves.size(); i++) {
			previous_moves.push_back(new Move(*board.previous_moves[i]));
		}

		if (last_move != NULL) {
			delete last_move;
			last_move = NULL;
		}

		if (board.last_move != NULL) {
			last_move = new Move(*board.last_move);
		}

		return *this;
	}

	uint64_t Board::get_pieces_for(Unit u) const
	{
		return pieces[u];
	}

	void Board::perform_move(const Move& m)
	{
		if (is_castling_move(m)) {
			perform_castling_move(m);
		} else {
			perform_regular_move(m);
		}

		whites_turn = !whites_turn;
		if(last_move != NULL) {
			delete last_move;
		}
		previous_moves.push_back(new Move(m));
		last_move = new Move(m);
	}

	bool Board::is_castling_move(const Move& move) const
	{
		if (!move.is_castling_move()) {
			return false;
		}

		if (is_whites_turn() && get_target_for_move(move.get_from_bit()) != WHITE_KING) {
			return false;
		} else if (!is_whites_turn() && get_target_for_move(move.get_from_bit()) != BLACK_KING) {
			return false;
		}

		return true;
	}

	void Board::perform_castling_move(const Move& m)
	{
		Move* second;

		if (m.get_to_coord() == "g1") {
			second = new Move("h1", "f1");
		} else if(m.get_to_coord() == "c1") {
			second = new Move("a1", "d1");
		} else if(m.get_to_coord() == "g8") {
			second = new Move("h8", "f8");
		} else if(m.get_to_coord() == "c8") {
			second = new Move("a8", "d8");
		}

		perform_regular_move(m);
		perform_regular_move(*second);

		delete second;
	}

	void Board::perform_regular_move(const Move& m)
	{
		uint64_t from, to;

		from = m.get_from_bit();
		to = m.get_to_bit();

		Unit mover = get_target_for_move(from);
		Unit target = get_target_for_move(to);

		if (mover == PIECES_SIZE) {
			std::cout << *this << std::endl;
			std::cout << "Attempted move: " <<  m.as_string() << std::endl;
			std::cout << std::hex << "--->\tbits: 0x" << m.get_from_bit() << " 0x" << m.get_to_bit() << std::dec << std::endl;
			if (!previous_moves.empty()) {
				for (size_t i = previous_moves.size()-1; i >= 0; i--) {
					std::cout << "Previous move: " <<  previous_moves[i]->as_string();
					std::cout << std::hex << "\tbits: 0x" << previous_moves[i]->get_from_bit() << " 0x" << previous_moves[i]->get_to_bit() << std::dec << std::endl;
				}
			}
			std::cout << "WSC: " << white_short_castling_available << std::endl;
			std::cout << "WLC: " << white_long_castling_available << std::endl;
			std::cout << "BSC: " << black_short_castling_available << std::endl;
			std::cout << "BLC: " << black_long_castling_available << std::endl;
		}
		assert ( mover != PIECES_SIZE );
		assert ( (pieces[mover] & from) != 0 );

		// Perform move
		pieces[mover] ^= from;
		pieces[mover] |= to;

		// Check if we 'take' a piece
		if (target != PIECES_SIZE) {
			pieces[target] ^= to;
			piece_taken = true;
		} else {
			piece_taken = false;
		}

		// Recalculate the totals

		// If we took a piece
		if (piece_taken) {
			if (whites_turn) {
				pieces[ALL_BLACK_PIECES] ^= to;
			} else {
				pieces[ALL_WHITE_PIECES] ^= to;
			}
		}

		// From
		if (whites_turn) {
			pieces[ALL_WHITE_PIECES] ^= from;
		} else {
			pieces[ALL_BLACK_PIECES] ^= from;
		}

		// To
		if (whites_turn) {
			pieces[ALL_WHITE_PIECES] |= to;
		} else {
			pieces[ALL_BLACK_PIECES] |= to;
		}

		check_castling_impact(m);
		check_pawn_promotion();
		update_board_control();
	}

	void Board::check_castling_impact(const Move& m)
	{
		if (!white_long_castling_available 
				&& !white_short_castling_available
				&& !black_long_castling_available
				&& !black_short_castling_available) 
		{
			return;
		}

		uint64_t from = m.get_from_bit();

		switch (from) {
			case static_cast<uint64_t>(0x10):
				white_short_castling_available = false;
				white_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x1):
				white_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x80):
				white_short_castling_available = false;
				break;
			case static_cast<uint64_t>(0x10)<<56:
				black_short_castling_available = false;
				black_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x1)<<56:
				black_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x80)<<56:
				black_short_castling_available = false;
				break;
		}
	}

	void Board::update_board_control()
	{
		ControlCalculator calc;

		white_control = calc.calculate_white_controlzone_for(*this);
		black_control = calc.calculate_black_controlzone_for(*this);
	}

	bool Board::is_white_in_check() const
	{
		return (black_control & get_pieces_for(WHITE_KING)) != 0;
	}

	bool Board::is_black_in_check() const
	{
		return (white_control & get_pieces_for(BLACK_KING)) != 0;
	}

	void Board::check_pawn_promotion()
	{
		// White pawns
		uint64_t pawns_to_promote = get_pieces_for(WHITE_PAWNS) & TOP_ROW;
		while (pawns_to_promote != 0) {
			uint64_t pawn = (pawns_to_promote & (pawns_to_promote-1)) ^ pawns_to_promote;
			pawns_to_promote &= pawns_to_promote-1;

			pieces[WHITE_PAWNS] ^= pawn;
			pieces[WHITE_QUEEN] |= pawn;
		}

		// Black pawns
		pawns_to_promote = get_pieces_for(BLACK_PAWNS) & BOTTOM_ROW;
		while (pawns_to_promote != 0) {
			uint64_t pawn = (pawns_to_promote & (pawns_to_promote-1)) ^ pawns_to_promote;
			pawns_to_promote &= pawns_to_promote-1;

			pieces[BLACK_PAWNS] ^= pawn;
			pieces[BLACK_QUEEN] |= pawn;
		}
	}

	Unit Board::get_target_for_move(uint64_t move) const
	{
		for (unsigned int i = WHITE_PAWNS; i <= BLACK_KING; i++) {
			if ((move & pieces[i]) != 0) {
				return static_cast<Unit>(i);
			}
		}

		return PIECES_SIZE;
	}

	std::ostream& operator<<(std::ostream& out, const cengine::Board& board)
	{
		using namespace cengine;

		uint64_t squareBit = 0x100000000000000;

		for(int i = 1; i <= 64; i++) {
			if((board.get_pieces_for(ALL_BLACK_PIECES) & squareBit) != 0) {
				if((board.get_pieces_for(BLACK_PAWNS) & squareBit) != 0)
					out << "P";
				else if((board.get_pieces_for(BLACK_ROOKS) & squareBit) != 0)
					out << "R";
				else if((board.get_pieces_for(BLACK_KNIGHTS) & squareBit) != 0)
					out << "N";
				else if((board.get_pieces_for(BLACK_BISHOPS) & squareBit) != 0)
					out << "B";
				else if((board.get_pieces_for(BLACK_QUEEN) & squareBit) != 0)
					out << "Q";
				else if((board.get_pieces_for(BLACK_KING) & squareBit) != 0)
					out << "K";
				else 
					out << "M";
			} else if((board.get_pieces_for(ALL_WHITE_PIECES) & squareBit) != 0) {
				if((board.get_pieces_for(WHITE_PAWNS) & squareBit) != 0)
					out << "p";
				else if((board.get_pieces_for(WHITE_ROOKS) & squareBit) != 0)
					out << "r";
				else if((board.get_pieces_for(WHITE_KNIGHTS) & squareBit) != 0)
					out << "n";
				else if((board.get_pieces_for(WHITE_BISHOPS) & squareBit) != 0)
					out << "b";
				else if((board.get_pieces_for(WHITE_QUEEN) & squareBit) != 0)
					out << "q";
				else if((board.get_pieces_for(WHITE_KING) & squareBit) != 0)
					out << "k";
				else 
					out << "m";
			} else {
				out << ".";
			}

			if(i % 8 == 0) {
				squareBit >>= 15;
				out << std::endl;
			} else {
				squareBit <<= 1;
				out << " ";
			}
		}

		return out;
	}

	std::istream& operator>>(std::istream& input, cengine::Board& b)
	{
		using namespace cengine;

		b.pieces[WHITE_PAWNS] 	= 0x0;
		b.pieces[WHITE_ROOKS] 	= 0x0;
		b.pieces[WHITE_KNIGHTS]	= 0x0;
		b.pieces[WHITE_BISHOPS]	= 0x0;
		b.pieces[WHITE_QUEEN]	= 0x0;
		b.pieces[WHITE_KING]	= 0x0;
		b.pieces[BLACK_PAWNS] 	= 0x0;
		b.pieces[BLACK_ROOKS] 	= 0x0;
		b.pieces[BLACK_KNIGHTS]	= 0x0;
		b.pieces[BLACK_BISHOPS]	= 0x0;
		b.pieces[BLACK_QUEEN]	= 0x0;
		b.pieces[BLACK_KING]	= 0x0;

		char square;
		uint64_t squareBit = 0x100000000000000;
		int unit_count = 0;
		int i = 0;

		while(input.good() && i < 64)
		{
			input >> square;

			Unit unit;

			switch(square)
			{
				case 'r':
					unit = WHITE_ROOKS;
					break;
				case 'n':
					unit = WHITE_KNIGHTS;
					break;
				case 'b':
					unit = WHITE_BISHOPS;
					break;
				case 'q':
					unit = WHITE_QUEEN;
					break;
				case 'k':
					unit = WHITE_KING;
					break;
				case 'p':
					unit = WHITE_PAWNS;
					break;
				case 'R':
					unit = BLACK_ROOKS;
					break;
				case 'N':
					unit = BLACK_KNIGHTS;
					break;
				case 'B':
					unit = BLACK_BISHOPS;
					break;
				case 'Q':
					unit = BLACK_QUEEN;
					break;
				case 'K':
					unit = BLACK_KING;
					break;
				case 'P':
					unit = BLACK_PAWNS;
					break;
				default:
					unit = PIECES_SIZE;
					break;
			}

			if(unit != PIECES_SIZE) {
				unit_count++;
				b.pieces[unit] |= squareBit;
			}

			i++;
			if(i % 8 == 0) {
				squareBit >>= 15;
			} else {
				squareBit <<= 1;
			}
		}

		b.pieces[ALL_WHITE_PIECES] = 0x0;
		b.pieces[ALL_BLACK_PIECES] = 0x0;

		for (int i = WHITE_PAWNS; i <= WHITE_KING; i++) {
			b.pieces[ALL_WHITE_PIECES] |= b.pieces[i];
		}
		for (int i = BLACK_PAWNS; i <= BLACK_KING; i++) {
			b.pieces[ALL_BLACK_PIECES] |= b.pieces[i];
		}

		b.piece_taken = unit_count < 32;

		uint64_t blackKingStart = 0x1000000000000000;
		uint64_t blackRookLeftStart = 0x100000000000000;
		uint64_t blackRookRightStart = 0x8000000000000000;
		uint64_t whiteKingStart = 0x10;
		uint64_t whiteRookLeftStart = 0x1;
		uint64_t whiteRookRightStart = 0x80;
		b.black_long_castling_available = false;
		b.black_short_castling_available = false;
		b.white_long_castling_available = false;
		b.white_short_castling_available = false;

		if((b.pieces[BLACK_KING] & blackKingStart) != 0) {
			if((b.pieces[BLACK_ROOKS] & blackRookLeftStart) != 0) {
				b.black_long_castling_available = true;
			}
			if((b.pieces[BLACK_ROOKS] & blackRookRightStart) != 0) {
				b.black_short_castling_available = true;
			}
		}

		if((b.pieces[WHITE_KING] & whiteKingStart) != 0) {
			if((b.pieces[WHITE_ROOKS] & whiteRookLeftStart) != 0) {
				b.white_long_castling_available = true;
			}
			if((b.pieces[WHITE_ROOKS] & whiteRookRightStart) != 0) {
				b.white_short_castling_available = true;
			}
		}

		b.whites_turn = true;
		b.last_move = NULL;

		return input;
	}
}
