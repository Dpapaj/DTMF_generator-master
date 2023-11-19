/*!
 * \file       dtmf.c
 * \author     Ondřej Ševčík
 * \date       9/2019
 * \brief      Implementation of DTMF generator module
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "dtmf.h"

#include "wavfile.h"

#include <math.h>
#include <stdbool.h>
#include <limits.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define VOLUME 1000
#define M_PI2  3.14159265358979323846

#define UNUSED(x) (void)x
/* Private variables -----------------------------------------------------------------------------*/
static double mSamplesLUT[WAVFILE_SAMPLES_PER_SECOND];

/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
/* Private function definitions ------------------------------------------------------------------*/

/* Function definition ----------------------------------------------------- */
bool DTMF_Generate(Vector_t *vector, char symbol) {
    if(vector == NULL)
    {
        return false;
    }

    static bool initialized = false;
    if (!initialized) {
    for (int i = 0; i < WAVFILE_SAMPLES_PER_SECOND; i++) {
      mSamplesLUT[i] = (double)i / WAVFILE_SAMPLES_PER_SECOND * 2 * M_PI;
    }
    initialized = true;
    }
    short lowFreq; //vyber z tabulky moodle
    short highFreq;

    switch (symbol) {
    case '0':
        lowFreq = 941;
        highFreq = 1336;
        break;
    case '1':
        lowFreq = 697;
        highFreq = 1209;
        break;
    case '2':
        lowFreq = 697;
        highFreq = 1336;
        break;
    case '3':
        lowFreq = 697;
        highFreq = 1477;
        break;
    case '4':
        lowFreq = 770;
        highFreq = 1209;
        break;
    case '5':
        lowFreq = 770;
        highFreq = 1336;
        break;
    case '6':
        lowFreq = 770;
        highFreq = 1477;
        break;
    case '7':
        lowFreq = 852;
        highFreq = 1209;
        break;
    case '8':
        lowFreq = 852;
        highFreq = 1336;
        break;
    case '9':
        lowFreq = 852;
        highFreq = 1477;
        break;
    case '#':
        lowFreq = 941;
        highFreq = 1477;
        break;
    case '*':
        lowFreq = 941;
        highFreq = 1209;
        break;
    case 'a':
        lowFreq = 697;
        highFreq = 1633;
        break;
    case 'A':
        lowFreq = 697;
        highFreq = 1633;
        break;
    case 'b':
        lowFreq = 770;
        highFreq = 1633;
        break;
    case 'B':
        lowFreq = 770;
        highFreq = 1633;
        break;
    case 'c':
        lowFreq = 852;
        highFreq = 1633;
        break;
    case 'C':
        lowFreq = 852;
        highFreq = 1633;
        break;
    case 'd':
        lowFreq = 941;
        highFreq = 1633;
        break;
    case 'D':
        lowFreq = 941;
        highFreq = 1633;
        break;
    case ' ':
        for (unsigned int i = 0; i < WAVFILE_SAMPLES_PER_SECOND; i++) {
            Vector_Append(vector, 0);
        }
        return true;
    default:
        return false;
    }

    for(int i = 0; i < WAVFILE_SAMPLES_PER_SECOND; i++)//maximalni 8000
    {
        //sin(2* pi * f * i/8000 Hz)
        double t = (double) i/WAVFILE_SAMPLES_PER_SECOND;
        double lowTone = sin(2 * lowFreq * t * M_PI2);
        double highTone = sin(2 * highFreq * t * M_PI2);
        short tone = (lowTone + highTone) * VOLUME;//short - typ vektoru
        Vector_Append(vector, tone);
    }

  return true;
}
