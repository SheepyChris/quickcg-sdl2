/*
QuickCG SDL2 20190709

Copyright (c) 2004-2007, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
QuickCG is an SDL 2.0 codebase that wraps some of the SDL 2.0 functionality.
It's used by Lode's Computer Graphics Tutorial to work with simple function calls
to demonstrate graphical programs. It may or may not be of industrial strength
for games, though I've actually used it for some.

QuickCG can handle some things that standard C++ does not but that are useful, such as:
-drawing graphics
-a bitmap font
-simplified saving and loading of files
-reading keyboard and mouse input
-playing sound
-color models
-loading images

Contact info:
My email address is (puzzle the account and domain together with an @ symbol):
Domain: gmail dot com.
Account: lode dot vandevenne.
*/

#ifndef _quickcg_h_included
#define _quickcg_h_included

#include <SDL.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm> //std::min and std::max

namespace QuickCG
{

////////////////////////////////////////////////////////////////////////////////
//useful templates//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//don't know why, but the standard C++ abs sometimes gives cryptic errors? if so use this :D
template<typename T>
const T template_abs(const T &a)
{
  return (a < 0) ? -a : a;
}

//usage: std::string str = valtostr(25454.91654654f);
template<typename T>
std::string valtostr(const T& val)
{
  std::ostringstream sstream;
  sstream << val;
  return sstream.str();
}

//usage: double val = strtoval<double>("465498.654");
template<typename T>
T strtoval(const std::string& s)
{
  std::istringstream sstream(s);
  T val;
  sstream >> val;
  return val;
}

//length is decimal precision of the floating point number
template<typename T>
std::string valtostr(const T& val, int length, bool fixed = true)
{
  std::ostringstream sstream;
  if(fixed) sstream << std::fixed;
  sstream << std::setprecision(length) << val;
  return sstream.str();
}

////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct ColorRGBA8bit;
//a color with 4 components: r, g, b and a
struct ColorRGBA
{
  int r;
  int g;
  int b;
  int a;

  ColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  ColorRGBA(const ColorRGBA8bit& color);
  ColorRGBA();
};

ColorRGBA operator+(const ColorRGBA& color, const ColorRGBA& color2);
ColorRGBA operator-(const ColorRGBA& color, const ColorRGBA& color2);
ColorRGBA operator*(const ColorRGBA& color, int a);
ColorRGBA operator*(int a, const ColorRGBA& color);
ColorRGBA operator/(const ColorRGBA& color, int a);
ColorRGBA overlay(const ColorRGBA& color, const ColorRGBA& color2);
bool operator==(const ColorRGBA& color, const ColorRGBA& color2);
bool operator!=(const ColorRGBA& color, const ColorRGBA& color2);

static const ColorRGBA RGB_Black    (  0,   0,   0, 255);
static const ColorRGBA RGB_Red		(255,   0,   0, 255);
static const ColorRGBA RGB_Green	(  0, 255,   0, 255);
static const ColorRGBA RGB_Blue		(  0,   0, 255, 255);
static const ColorRGBA RGB_Cyan		(  0, 255, 255, 255);
static const ColorRGBA RGB_Magenta	(255,   0, 255, 255);
static const ColorRGBA RGB_Yellow	(255, 255,   0, 255);
static const ColorRGBA RGB_White	(255, 255, 255, 255);
static const ColorRGBA RGB_Gray		(128, 128, 128, 255);
static const ColorRGBA RGB_Grey		(192, 192, 192, 255);
static const ColorRGBA RGB_Maroon	(128,   0,   0, 255);
static const ColorRGBA RGB_Darkgreen(  0, 128,   0, 255);
static const ColorRGBA RGB_Navy		(  0,   0, 128, 255);
static const ColorRGBA RGB_Teal		(  0, 128, 128, 255);
static const ColorRGBA RGB_Purple	(128,   0, 128, 255);
static const ColorRGBA RGB_Olive	(128, 128,   0, 255);

//a color with 4 components: r, g, b and a
struct ColorRGBA8bit
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;

  ColorRGBA8bit(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  ColorRGBA8bit(const ColorRGBA& color);
  ColorRGBA8bit();
};

//a color with 3 components: h, s and l
struct ColorHSL
{
  int h;
  int s;
  int l;
  int a;

  ColorHSL(Uint8 h, Uint8 s, Uint8 l, Uint8 a);
  ColorHSL();
};

//a color with 3 components: h, s and v
struct ColorHSV
{
  int h;
  int s;
  int v;
  int a;

  ColorHSV(Uint8 h, Uint8 s, Uint8 v, Uint8 a);
  ColorHSV();
};

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern int w;
extern int h;

////////////////////////////////////////////////////////////////////////////////
//KEYBOARD FUNCTIONS////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool keyDown(int key); //this checks if the key is held down, returns true all the time until the key is up
bool keyPressed(int key); //this checks if the key is *just* pressed, returns true only once until the key is up again

////////////////////////////////////////////////////////////////////////////////
//BASIC SCREEN FUNCTIONS////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void screen(int width = 640, int height = 400, bool fullscreen = 0, const std::string& text = " ");
void lock();
void unlock();
void redraw();
void cls(const ColorRGBA& color = RGB_Black);
void pset(int x, int y, const ColorRGBA& color);
ColorRGBA pget(int x, int y);
void drawBuffer(Uint32* buffer);
bool onScreen(int x, int y);

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FUNCTIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void sleep();
void sleep(double seconds);
void waitFrame(double oldTime, double frameDuration); //in seconds
bool done(bool quit_if_esc = true, bool delay = true);
void end();
void readKeys();
void getMouseState(int& mouseX, int& mouseY);
void getMouseState(int& mouseX, int& mouseY, bool& LMB, bool& RMB);
unsigned long getTicks(); //ticks in milliseconds
inline double getTime() { return getTicks() / 1000.0; } //time in seconds

////////////////////////////////////////////////////////////////////////////////
//2D SHAPES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool horLine(int y, int x1, int x2, const ColorRGBA& color);
bool verLine(int x, int y1, int y2, const ColorRGBA& color);
bool drawLine(int x1, int y1, int x2, int y2, const ColorRGBA& color);
bool drawCircle(int xc, int yc, int radius, const ColorRGBA& color);
bool drawDisk(int xc, int yc, int radius, const ColorRGBA& color);
bool drawRect(int x1, int y1, int x2, int y2, const ColorRGBA& color);
bool clipLine(int x1,int y1,int x2, int y2, int & x3, int & y3, int & x4, int & y4);

////////////////////////////////////////////////////////////////////////////////
//COLOR CONVERSIONS/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ColorHSL RGBtoHSL(const ColorRGBA& ColorRGBA);
ColorRGBA HSLtoRGB(const ColorHSL& colorHSL);
ColorHSV RGBtoHSV(const ColorRGBA& ColorRGBA);
ColorRGBA HSVtoRGB(const ColorHSV& colorHSV);
Uint32 RGBtoINT(const ColorRGBA& ColorRGBA);
ColorRGBA INTtoRGB(Uint32 colorINT);

////////////////////////////////////////////////////////////////////////////////
//FILE FUNCTIONS////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void loadFile(std::vector<unsigned char>& buffer, const std::string& filename);
void saveFile(const std::vector<unsigned char>& buffer, const std::string& filename);

////////////////////////////////////////////////////////////////////////////////
//IMAGE FUNCTIONS///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int loadImage(std::vector<ColorRGBA>& out, unsigned long& w, unsigned long& h, const std::string& filename);
int loadImage(std::vector<Uint32>& out, unsigned long& w, unsigned long& h, const std::string& filename);
int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
int decodePNG(std::vector<unsigned char>& out_image_32bit, unsigned long& image_width, unsigned long& image_height, const std::vector<unsigned char>& in_png);

////////////////////////////////////////////////////////////////////////////////
//TEXT FUNCTIONS////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
extern bool font[256][8][8];
void drawLetter(unsigned char n, int x, int y, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black);
int printString(const std::string& text, int x = 0, int y = 0, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black, int forceLength = 0);

//print something (string, int, float, ...)
template<typename T>
int print(const T& val, int x = 0, int y = 0, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black, int forceLength = 0)
{
  std::string text = valtostr(val);
  return printString(text, x, y, color, bg, color2, forceLength);
}

//print some floating point number, this one allows printing floating point numbers with limited length
template<typename T>
int fprint(const T& val, int length, int x = 0, int y = 0, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black, int forceLength = 0)
{
  std::string text = valtostr(val, length, true);
  return printString(text, x, y, color, bg, color2, forceLength);
}

////////////////////////////////////////////////////////////////////////////////
//TEXT INPUT FUNCTIONS//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Uint8 getInputCharacter();
void getInputString(std::string& text, const std::string& message = "", bool clear = false, int x = 0, int y = 0, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black);

template<typename T>
T getInput(const std::string& message = "", bool clear = false, int x = 0, int y = 0, const ColorRGBA& color = RGB_White, bool bg = 0, const ColorRGBA& color2 = RGB_Black)
{
  std::string text;
  getInputString(text, message, clear, x, y, color, bg, color2);
  return strtoval<T>(text);
}

////////////////////////////////////////////////////////////////////////////////
//SOUNDCARD FUNCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int audioOpen(int samplerate, int framesize); //always 16-bit mono sound for now; returns 0 if no error happened
void audioClose();
int audioReOpen(); //closes and opens again with same parameters

/*
push samples to the soundcard, making sure not to cause shortage or overflow
pos and end are the range in the samples vector that you want to push to the audio card
*/
void audioPushSamples(const std::vector<double>& samples, size_t pos, size_t end);

size_t audioSamplesShortage(); //returns value > 0 if the soundcard is consuming more samples than you're producing
size_t audioSamplesOverflow(); //returns value > 0 if you're producing more samples than the soundard is consuming - so take it easy a bit
void audioSetBufferSamplesRange(size_t min_samples, size_t max_samples); //set shortage and overflow values. E.g. 4096 and 8192.

/*
This plays the sound starting at this time, until it's done
The difference with audioPushSamples is:
audioPlay allows playing multiple sounds at the same time: it doesn't push at the end,
but elementwise-adds or pushes back samples if needed.
The duration depends on samplerate, make sure the samples in the vector have the correct samplerate.
*/
void audioPlay(const std::vector<double>& samples);

void audioSetMode(int mode); //0: silent, 1: full (no volume calculations ==> faster), 2: volume-controlled (= default value)
void audioSetVolume(double volume); //multiplier used if mode is 2 (volume-controlled). Default value is 1.0.

} //end of namespace QuickCG

#endif


