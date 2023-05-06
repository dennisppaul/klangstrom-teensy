#ifndef KLANGSTROM_TEENSY_H
#define KLANGSTROM_TEENSY_H

#include <Audio.h>

extern void audioblock_transmit(float* pLeft, float* pRight);
#define KLANG_SAMPLES_PER_AUDIO_BLOCK AUDIO_BLOCK_SAMPLES

// @TODO add input
// @TODO sort out block size definition
// @TODO implememt update function similar to Klangstrom

class KlangstromTeensy : public AudioStream {
private:
    float mLeftTX[KLANG_SAMPLES_PER_AUDIO_BLOCK];
    float mRightTX[KLANG_SAMPLES_PER_AUDIO_BLOCK];

public:
    KlangstromTeensy() : AudioStream(0, NULL) {
        //@TODO(check if AUDIO_BLOCK_SAMPLES == KLANG_SAMPLES_PER_AUDIO_BLOCK*2)
    }

    void update(void) {
        audio_block_t* block;
        block = allocate();

        if (block == NULL) {
            return;
        }

        audioblock_transmit(mLeftTX, mRightTX);

        for (uint32_t i = 0; i < AUDIO_BLOCK_SAMPLES; i += 2) {
            block->data[i + 0] = (mLeftTX[i / 2] + 1.0) * (1 << 14);
            block->data[i + 1] = (mRightTX[i / 2] + 1.0) * (1 << 14);
        }

        transmit(block);
        release(block);
    }
};

#endif  // KLANGSTROM_TEENSY_H
