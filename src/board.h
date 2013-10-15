#ifndef _BOARD_H
#define _BOARD_H

#include <cstdint>
#include <iostream>

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
			uint64_t pieces[PIECES_SIZE];
			bool white_long_castling_available, black_long_castling_available;
			bool white_short_castling_available, black_short_castling_available;
			bool piece_taken;
			bool whites_turn;
			Move* last_move;

			Unit get_target_for_move(uint64_t);

			void perform_castling_move(const Move&);

			void perform_regular_move(const Move&);

			void check_castling_impact(const Move&);

		public:

			Board();

			Board(const Board&);

			Board(std::ifstream&);

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

			void perform_move(const Move&);

			friend std::ostream& operator<<(std::ostream&, const Board&);
	};
}

#endif
