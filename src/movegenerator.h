#ifndef _MOVE_GENERATOR_H
#define _MOVE_GENERATOR_H

#include <vector>
#include "board.h"

namespace cengine
{
	enum Direction {
		UP,
		UP_RIGHT,
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT
	};

	class MoveGenerator
	{
		public: // Subclasses
			class iterator
			{
				private:
					std::vector<Board>::iterator iter;
				public:
					iterator(const std::vector<Board>::iterator& i) : iter(i) { }
					iterator& operator++() { iter++; return *this; }
					iterator operator++(int) { iterator tmp(*this); iter++; return tmp; }
					Board& operator*() { return *iter; }
					bool operator==(const iterator& i) { return iter == i.iter; }
					bool operator!=(const iterator& i) { return iter != i.iter; }
			};

			class const_iterator
			{
				private:
					std::vector<Board>::const_iterator iter;
				public:
					const_iterator(const std::vector<Board>::const_iterator& i) : iter(i) { }
					const_iterator& operator++() { iter++; return *this; }
					const_iterator operator++(int) { const_iterator tmp(*this); iter++; return tmp; }
					const Board& operator*() { return *iter; }
					bool operator==(const const_iterator& i) { return iter == i.iter; }
					bool operator!=(const const_iterator& i) { return iter != i.iter; }
			};

		private:

			std::vector<Board> possible_moves;

		public: // Methods

			void calculate_moves_for(const Board&);

			std::size_t move_count();

			iterator begin() { return iterator(possible_moves.begin()); }
			iterator end() { return iterator(possible_moves.end()); }

			const_iterator begin() const 
			{
				return const_iterator(possible_moves.begin());
			}

			const_iterator end() const 
			{
				return const_iterator(possible_moves.end());
			}

		private: // Methods

			void calculate_pawn_moves_for(const Board&);
			void calculate_rook_moves_for(const Board&);
			void calculate_knight_moves_for(const Board&);
			void calculate_bishop_moves_for(const Board&);
			void calculate_queen_moves_for(const Board&);
			void calculate_king_moves_for(const Board&);
			void calculate_castling_moves(const Board&);

			void calculate_direction_moves(const Board&, const uint64_t, const Direction);
			uint64_t shift_piece(const uint64_t, const Direction);
			void add_move(const Board&, uint64_t, uint64_t);
	};
}

#endif
