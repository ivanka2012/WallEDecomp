#pragma once

/**
 * @brief The RNG
 * Taken from Chapter 7, page 280 of Numerical Recipes, 2nd edition, presumably by Kalisto
 * A truly fascinating piece of computing history just sitting here in WALL-E...
 * 
 * First verified to match: 2024-03-19 22:19:29
 * 
 * @param idum 
 * @return float 
 */

float ran1(long *idum);

/**
 * @brief Initialize the ran1 RNG with the seed
 * 
 * First verified to match: 2024-03-21 22:49:19
 * 
 * @param seed 
 */

void InitRandom(long seed);

long Alea(long i_Min, long i_Max);
float Random();