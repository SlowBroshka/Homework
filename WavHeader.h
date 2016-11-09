//
// Created by slowbro on 18.10.16.
//

#ifndef SIGNALENCODING_WAVHEADER_H
#define SIGNALENCODING_WAVHEADER_H


typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    char            RIFF[4];        // RIFF Header Magic header
    unsigned int   ChunkSize;      // RIFF Chunk Size
    char            WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    char            fmt[4];         // FMT header
    unsigned int   Subchunk1Size;  // Size of the fmt chunk
    unsigned short  AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    unsigned short  NumOfChan;      // Number of channels 1=Mono 2=Sterio
    unsigned int   SamplesPerSec;  // Sampling Frequency in Hz
    unsigned int   bytesPerSec;    // bytes per second
    unsigned short  blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    unsigned short  bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    char            Subchunk2ID[4]; // "data"  string
    unsigned int    Subchunk2Size;  // Sampled data length
} wav_hdr;

#endif //SIGNALENCODING_WAVHEADER_H
