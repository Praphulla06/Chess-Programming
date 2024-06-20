
// System Headers

#include <iostream>
#include <stdint.h>
#include <stdio.h>

// Bit Manipulations

// define bitboard data type
typedef uint64_t U64;

// board squares
enum
{
    a8,b8,c8,d8,e8,f8,g8,h8,
    a7,b7,c7,d7,e7,f7,g7,h7,
    a6,b6,c6,d6,e6,f6,g6,h6,
    a5,b5,c5,d5,e5,f5,g5,h5,
    a4,b4,c4,d4,e4,f4,g4,h4,
    a3,b3,c3,d3,e3,f3,g3,h3,
    a2,b2,c2,d2,e2,f2,g2,h2,
    a1,b1,c1,d1,e1,f1,g1,h1,
};

enum {white, black};
// "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
// "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
// "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
// "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
// "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
// "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
// "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
// "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",

// get/set/pop functions
int get_bit(U64 bitboard, int sqaure)
{
    return bitboard & (1ULL << sqaure) ? 1 : 0;
}
void set_bit(U64 &bitboard, int square)
{
    bitboard |= (1ULL << square);
}

void pop_bit(U64 &bitboard, int sqaure)
{
    get_bit(bitboard, sqaure) ? bitboard ^= (1ULL << sqaure): 0;
}


void print_bitboard(U64 bitboard)
{
    std::cout << std::endl;
    // loop over board ranks
    for (int rank = 0; rank < 8; rank++)
    {
        // loop over board files
        for (int file = 0; file < 8; file++)
        {
            // convert file & rank into sqaure index
            int sqaure = rank * 8 + file;

            if (!file)
                std::cout << " " << (8 - rank);

            std::cout << " " << get_bit(bitboard, sqaure);
        }
        std::cout << std::endl;
    }

    // print board files
    std::cout << std::endl
              << "   a b c d e f g h" << std::endl;

    // print bitboard as unsigned decimal number

    std::cout << std::endl
              << "   Bitboard: " << bitboard << "d" << std::endl;
}
// not A file

//  8 0 1 1 1 1 1 1 1
//  7 0 1 1 1 1 1 1 1
//  6 0 1 1 1 1 1 1 1
//  5 0 1 1 1 1 1 1 1
//  4 0 1 1 1 1 1 1 1
//  3 0 1 1 1 1 1 1 1
//  2 0 1 1 1 1 1 1 1
//  1 0 1 1 1 1 1 1 1

//    a b c d e f g h


// not A file constant
const U64 not_a_file = 18374403900871474942ULL;


//not H file
// 17, 15, 10, 6
//  8 1 1 1 1 1 1 1 0
//  7 1 1 1 1 1 1 1 0
//  6 1 1 1 1 1 1 1 0
//  5 1 1 1 1 1 1 1 0
//  4 1 1 1 1 1 1 1 0
//  3 1 1 1 1 1 1 1 0
//  2 1 1 1 1 1 1 1 0
//  1 1 1 1 1 1 1 1 0

//    a b c d e f g h

// not H file constant

const U64 not_h_file = 9187201950435737471ULL;

// not HG file

//  8 1 1 1 1 1 1 0 0
//  7 1 1 1 1 1 1 0 0
//  6 1 1 1 1 1 1 0 0
//  5 1 1 1 1 1 1 0 0
//  4 1 1 1 1 1 1 0 0
//  3 1 1 1 1 1 1 0 0
//  2 1 1 1 1 1 1 0 0
//  1 1 1 1 1 1 1 0 0

//    a b c d e f g h

// not HG file constant
const U64 not_hg_file = 4557430888798830399ULL;


//not AB file
//  8 0 0 1 1 1 1 1 1
//  7 0 0 1 1 1 1 1 1
//  6 0 0 1 1 1 1 1 1
//  5 0 0 1 1 1 1 1 1
//  4 0 0 1 1 1 1 1 1
//  3 0 0 1 1 1 1 1 1
//  2 0 0 1 1 1 1 1 1
//  1 0 0 1 1 1 1 1 1

//    a b c d e f g h

//not AB file constant
const U64 not_ab_file = 18229723555195321596ULL;
// Pawn attack table [sides][sqaure]
U64 pawn_attacks[2][64];

// kingith attacks table [sqaure]

U64 knight_attacks[64];

// king attacks table [sqaure]
U64 king_attacks[64];

U64 mask_pawn_attacks(int side, int sqaure)
{
    //  result attacks bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    // set piece on board

    set_bit(bitboard, sqaure);
    // print_bitboard(bitboard);


    // white pawns
    if (!side)
    {
        // generate pawn attacks
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);

    }

    //black pawns
    else
    {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    }

    // return attack map
    return attacks;
}

// generate knight attacks

U64 mask_knight_attacks(int sqaure)
{
//  result attacks bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    // set piece on board

    set_bit(bitboard, sqaure);   

    //generate knight attacks 17, 15, 10, 6
    if ((bitboard >> 17) & not_h_file)  attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file)  attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_hg_file)  attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file)  attacks |= (bitboard >> 6);
    
    if ((bitboard << 17) & not_a_file)  attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file)  attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file)  attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_hg_file)  attacks |= (bitboard << 6);
    

    //return attack map
    return attacks; 

}

// generate king attacks

U64 mask_king_attacks(int sqaure)
{
    //  result attacks bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    // set piece on board

    set_bit(bitboard, sqaure);   

    //generate king attacks 17, 15, 10, 6

    if (bitboard >> 8) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);

    if ((bitboard << 8)) attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);
    // attacks |= (bitboard << 7);
    // attacks |= (bitboard << 8);
    // attacks |= (bitboard << 9);
    // attacks |= (bitboard << 1);


    //return attack map
    return attacks; 
}

// mask bishop attacks

U64 mask_bishop_attacks(int sqaure)
{
    // result attacks bitboard

    U64 attacks = 0ULL;

    // init ranks & files
    int r, f;

    // intit target rank & files
    int tr = sqaure / 8;
    int tf = sqaure % 8;

    // mask relevant bishop occupancy bits

    for (r = tr + 1, f = tf + 1; (r <= 6 && f <= 6); r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; (r >= 1 && f <= 6); r--, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; (r <= 6 && f >= 1); r++, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1; (r >= 1 && f >= 1); r--, f--) attacks |= (1ULL << (r * 8 + f));
    


    // return attack map
    return attacks;
}

// mask rook attacks
U64 mask_rook_attacks(int sqaure)
{
    // result attacks bitboard

    U64 attacks = 0ULL;

    // init ranks & files
    int r, f;

    // intit target rank & files
    int tr = sqaure / 8;
    int tf = sqaure % 8;

    // mask relevant rook occupancy bits    
    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));

    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));

    // return attack map
    return attacks;
}

// init leaper pieces attacks

void init_leapers_attacks()
{
    // loop over 64 board sqaures
    for (int sqaure = 0; sqaure < 64; sqaure++)
    {
        // init pawn attacks
        pawn_attacks[white][sqaure] = mask_pawn_attacks(white, sqaure);
        pawn_attacks[black][sqaure] = mask_pawn_attacks(black, sqaure);

        //init knight attacks
        knight_attacks[sqaure] = mask_knight_attacks(sqaure);


        // init king attacks
        king_attacks[sqaure] = mask_king_attacks(sqaure);


    }
}

// Main Function
int main()
{
    // init leaper pieces attacks
    init_leapers_attacks();

    for (int sqaure = 0; sqaure < 64; sqaure++)
    {
            print_bitboard(mask_rook_attacks(sqaure));

    }

    return 0;
}
