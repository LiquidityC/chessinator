#include <cassert>
#include <fstream>
#include <iostream>

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
		whites_turn = board.is_whites_turn();

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
		if (m.is_castling_move()) {
			perform_castling_move(m);
		} else {
			perform_regular_move(m);
		}

		whites_turn = !whites_turn;
		if(last_move != NULL) {
			delete last_move;
		}
		last_move = new Move(m);
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
			std::cout << m.as_string() << std::endl;

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
		// From
		if ((pieces[ALL_WHITE_PIECES] & from) != 0) {
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

		uint64_t to = m.get_to_bit();

		if ((to & pieces[WHITE_KING]) != 0) {
			white_long_castling_available = false;
			white_short_castling_available = false;
		} else if ((to & pieces[BLACK_KING]) != 0) {
			black_short_castling_available = false;
			black_long_castling_available = false;
		}

		uint64_t rook_left_start = 0x1;
		uint64_t rook_right_start = 0x80;
		if ( (to & rook_left_start) != 0 ) {
			white_long_castling_available = false;
		} else if ( (to & rook_right_start) != 0 ) {
			white_short_castling_available = false;
		} else if ( (to & rook_left_start<<56) != 0 ) {
			black_long_castling_available = false;
		} else if ( (to & rook_right_start<<56) != 0 ) {
			black_short_castling_available = false;
		}
	}

	Unit Board::get_target_for_move(uint64_t move)
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

		for(int i = 1; i <= 64; i++)
		{
			if((board.get_pieces_for(ALL_BLACK_PIECES) & squareBit) != 0)
			{
				if((board.get_pieces_for(BLACK_PAWNS) & squareBit) != 0)
					out << "P";
				if((board.get_pieces_for(BLACK_ROOKS) & squareBit) != 0)
					out << "R";
				if((board.get_pieces_for(BLACK_KNIGHTS) & squareBit) != 0)
					out << "N";
				if((board.get_pieces_for(BLACK_BISHOPS) & squareBit) != 0)
					out << "B";
				if((board.get_pieces_for(BLACK_QUEEN) & squareBit) != 0)
					out << "Q";
				if((board.get_pieces_for(BLACK_KING) & squareBit) != 0)
					out << "K";
			}
			else if((board.get_pieces_for(ALL_WHITE_PIECES) & squareBit) != 0)
			{
				if((board.get_pieces_for(WHITE_PAWNS) & squareBit) != 0)
					out << "p";
				if((board.get_pieces_for(WHITE_ROOKS) & squareBit) != 0)
					out << "r";
				if((board.get_pieces_for(WHITE_KNIGHTS) & squareBit) != 0)
					out << "n";
				if((board.get_pieces_for(WHITE_BISHOPS) & squareBit) != 0)
					out << "b";
				if((board.get_pieces_for(WHITE_QUEEN) & squareBit) != 0)
					out << "q";
				if((board.get_pieces_for(WHITE_KING) & squareBit) != 0)
					out << "k";
			}
			else
			{
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
		b.pieces[WHITE_QUEEN]		= 0x0;
		b.pieces[WHITE_KING]		= 0x0;
		b.pieces[BLACK_PAWNS] 	= 0x0;
		b.pieces[BLACK_ROOKS] 	= 0x0;
		b.pieces[BLACK_KNIGHTS]	= 0x0;
		b.pieces[BLACK_BISHOPS]	= 0x0;
		b.pieces[BLACK_QUEEN]		= 0x0;
		b.pieces[BLACK_KING]		= 0x0;

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
