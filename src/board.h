#ifndef _BOARD_H
#define _BOARD_H

#include <cstdint>
#include <iostream>
#include <vector>
#include "move.h"

namespace cengine
{
	class Move;

	enum Unit {
		WHITE_PAWNS,
		WHITE_ROOKS,
		WHITE_KNIGHTS,
		WHITE_BISHOPS,
		WHITE_QUEEN,
		WHITE_KING,
		BLACK_PAWNS,
		BLACK_ROOKS,
		BLACK_KNIGHTS,
		BLACK_BISHOPS,
		BLACK_QUEEN,
		BLACK_KING,
		ALL_WHITE_PIECES,
		ALL_BLACK_PIECES,
		PIECES_SIZE
	};

	class Board
	{
		private:

			/* Variables */
			uint64_t pieces[PIECES_SIZE];

			uint64_t white_control;
			uint64_t black_control;

			bool white_long_castling_available, black_long_castling_available;
			bool white_short_castling_available, black_short_castling_available;

			bool piece_taken;
			bool whites_turn;

			Move* last_move;
			std::vector<Move*> previous_moves;

			/* Functions */
			Unit get_target_for_move(uint64_t) const;

			bool is_castling_move(const Move&) const;
			void perform_castling_move(const Move&);

			void perform_regular_move(const Move&);

			void check_castling_impact(const Move&);

			void update_board_control();

		public:

			Board();

			Board(const Board&);

			~Board();

			Board& operator=(const Board&);

			uint64_t get_pieces_for(Unit) const;

			bool is_whites_turn() const { return whites_turn; }
			void set_whites_turn(bool whites_turn) { this->whites_turn = whites_turn; }

			bool is_piece_taken() const { return piece_taken; }
			bool is_white_long_castling_available() const { return white_long_castling_available; }
			bool is_white_short_castling_available() const { return white_short_castling_available; }
			bool is_black_long_castling_available() const { return black_long_castling_available; }
			bool is_black_short_castling_available() const { return black_short_castling_available; }

			Move get_last_move() const { return *last_move; }

			void perform_move(const Move&);

			uint64_t get_white_control() const { return white_control; }
			uint64_t get_black_control() const { return black_control; }

			bool is_white_in_check() const;
			bool is_black_in_check() const;

			void check_pawn_promotion();

			friend std::ostream& operator<<(std::ostream&, const Board&);

			friend std::istream& operator>>(std::istream&, Board&);
	};
}

#endif
