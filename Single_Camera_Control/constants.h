#pragma once

#include <pylon/PylonIncludes.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include <pylon/1394/Basler1394InstantCamera.h>
#include "Resource.h"
#include <vector>
#include <array>

#define PIXIS_SAFEMODE false

// The code compiles fairly differently for Firewire (1384) cameras vs. USB cameras.
const std::string mainColor = "Dark Grey";
const std::string DATA_SAVE_LOCATION = "J:\\Data Repository\\New Data Repository\\";
const std::string DATA_SAVE_LOCATION2 = "\\Raw Data\\PixisData_";

// constants for various controls that I need to reference in the basler window message map. Boring controls start at 
// 1000.
#define IDC_MIN_SLIDER_EDIT 10001
#define IDC_MAX_SLIDER_EDIT 10002
#define IDC_CAMERA_MODE_COMBO 10003
#define IDC_EXPOSURE_MODE_COMBO 10004
#define IDC_REPETITIONS_EDIT 10005
#define IDC_TRIGGER_MODE_COMBO 10006
#define IDC_SET_ANALYSIS_LOCATIONS 10007
// the basler has a 10 bit dac, but the data is compressed to 256 for visualization (visualization only!)
#define PICTURE_PALETTE_SIZE 256


// a colormap that I use for plot stuffs.
	const std::vector<std::array<int, 3>> GIST_RAINBOW_RGB{ { 255 , 0 , 40 },
	{ 255 , 0 , 35 },
	{ 255 , 0 , 30 },
	{ 255 , 0 , 24 },
	{ 255 , 0 , 19 },
	{ 255 , 0 , 14 },
	{ 255 , 0 , 8 },
	{ 255 , 0 , 3 },
	{ 255 , 1 , 0 },
	{ 255 , 7 , 0 },
	{ 255 , 12 , 0 },
	{ 255 , 18 , 0 },
	{ 255 , 23 , 0 },
	{ 255 , 28 , 0 },
	{ 255 , 34 , 0 },
	{ 255 , 39 , 0 },
	{ 255 , 45 , 0 },
	{ 255 , 50 , 0 },
	{ 255 , 55 , 0 },
	{ 255 , 61 , 0 },
	{ 255 , 66 , 0 },
	{ 255 , 72 , 0 },
	{ 255 , 77 , 0 },
	{ 255 , 82 , 0 },
	{ 255 , 88 , 0 },
	{ 255 , 93 , 0 },
	{ 255 , 99 , 0 },
	{ 255 , 104 , 0 },
	{ 255 , 110 , 0 },
	{ 255 , 115 , 0 },
	{ 255 , 120 , 0 },
	{ 255 , 126 , 0 },
	{ 255 , 131 , 0 },
	{ 255 , 137 , 0 },
	{ 255 , 142 , 0 },
	{ 255 , 147 , 0 },
	{ 255 , 153 , 0 },
	{ 255 , 158 , 0 },
	{ 255 , 164 , 0 },
	{ 255 , 169 , 0 },
	{ 255 , 174 , 0 },
	{ 255 , 180 , 0 },
	{ 255 , 185 , 0 },
	{ 255 , 191 , 0 },
	{ 255 , 196 , 0 },
	{ 255 , 201 , 0 },
	{ 255 , 207 , 0 },
	{ 255 , 212 , 0 },
	{ 255 , 218 , 0 },
	{ 255 , 223 , 0 },
	{ 255 , 228 , 0 },
	{ 255 , 234 , 0 },
	{ 255 , 239 , 0 },
	{ 255 , 245 , 0 },
	{ 255 , 250 , 0 },
	{ 254 , 255 , 0 },
	{ 248 , 255 , 0 },
	{ 243 , 255 , 0 },
	{ 237 , 255 , 0 },
	{ 232 , 255 , 0 },
	{ 227 , 255 , 0 },
	{ 221 , 255 , 0 },
	{ 216 , 255 , 0 },
	{ 210 , 255 , 0 },
	{ 205 , 255 , 0 },
	{ 199 , 255 , 0 },
	{ 194 , 255 , 0 },
	{ 189 , 255 , 0 },
	{ 183 , 255 , 0 },
	{ 178 , 255 , 0 },
	{ 172 , 255 , 0 },
	{ 167 , 255 , 0 },
	{ 162 , 255 , 0 },
	{ 156 , 255 , 0 },
	{ 151 , 255 , 0 },
	{ 145 , 255 , 0 },
	{ 140 , 255 , 0 },
	{ 135 , 255 , 0 },
	{ 129 , 255 , 0 },
	{ 124 , 255 , 0 },
	{ 118 , 255 , 0 },
	{ 113 , 255 , 0 },
	{ 108 , 255 , 0 },
	{ 102 , 255 , 0 },
	{ 97 , 255 , 0 },
	{ 91 , 255 , 0 },
	{ 86 , 255 , 0 },
	{ 81 , 255 , 0 },
	{ 75 , 255 , 0 },
	{ 70 , 255 , 0 },
	{ 64 , 255 , 0 },
	{ 59 , 255 , 0 },
	{ 54 , 255 , 0 },
	{ 48 , 255 , 0 },
	{ 43 , 255 , 0 },
	{ 37 , 255 , 0 },
	{ 32 , 255 , 0 },
	{ 27 , 255 , 0 },
	{ 21 , 255 , 0 },
	{ 16 , 255 , 0 },
	{ 10 , 255 , 0 },
	{ 5 , 255 , 0 },
	{ 0 , 255 , 0 },
	{ 0 , 255 , 5 },
	{ 0 , 255 , 10 },
	{ 0 , 255 , 16 },
	{ 0 , 255 , 21 },
	{ 0 , 255 , 26 },
	{ 0 , 255 , 32 },
	{ 0 , 255 , 37 },
	{ 0 , 255 , 43 },
	{ 0 , 255 , 48 },
	{ 0 , 255 , 53 },
	{ 0 , 255 , 59 },
	{ 0 , 255 , 64 },
	{ 0 , 255 , 69 },
	{ 0 , 255 , 75 },
	{ 0 , 255 , 80 },
	{ 0 , 255 , 86 },
	{ 0 , 255 , 91 },
	{ 0 , 255 , 96 },
	{ 0 , 255 , 102 },
	{ 0 , 255 , 107 },
	{ 0 , 255 , 112 },
	{ 0 , 255 , 118 },
	{ 0 , 255 , 123 },
	{ 0 , 255 , 129 },
	{ 0 , 255 , 134 },
	{ 0 , 255 , 139 },
	{ 0 , 255 , 145 },
	{ 0 , 255 , 150 },
	{ 0 , 255 , 155 },
	{ 0 , 255 , 161 },
	{ 0 , 255 , 166 },
	{ 0 , 255 , 172 },
	{ 0 , 255 , 177 },
	{ 0 , 255 , 182 },
	{ 0 , 255 , 188 },
	{ 0 , 255 , 193 },
	{ 0 , 255 , 198 },
	{ 0 , 255 , 204 },
	{ 0 , 255 , 209 },
	{ 0 , 255 , 215 },
	{ 0 , 255 , 220 },
	{ 0 , 255 , 225 },
	{ 0 , 255 , 231 },
	{ 0 , 255 , 236 },
	{ 0 , 255 , 241 },
	{ 0 , 255 , 247 },
	{ 0 , 255 , 252 },
	{ 0 , 251 , 255 },
	{ 0 , 246 , 255 },
	{ 0 , 241 , 255 },
	{ 0 , 235 , 255 },
	{ 0 , 230 , 255 },
	{ 0 , 224 , 255 },
	{ 0 , 219 , 255 },
	{ 0 , 213 , 255 },
	{ 0 , 208 , 255 },
	{ 0 , 202 , 255 },
	{ 0 , 197 , 255 },
	{ 0 , 192 , 255 },
	{ 0 , 186 , 255 },
	{ 0 , 181 , 255 },
	{ 0 , 175 , 255 },
	{ 0 , 170 , 255 },
	{ 0 , 164 , 255 },
	{ 0 , 159 , 255 },
	{ 0 , 154 , 255 },
	{ 0 , 148 , 255 },
	{ 0 , 143 , 255 },
	{ 0 , 137 , 255 },
	{ 0 , 132 , 255 },
	{ 0 , 126 , 255 },
	{ 0 , 121 , 255 },
	{ 0 , 116 , 255 },
	{ 0 , 110 , 255 },
	{ 0 , 105 , 255 },
	{ 0 , 99 , 255 },
	{ 0 , 94 , 255 },
	{ 0 , 88 , 255 },
	{ 0 , 83 , 255 },
	{ 0 , 77 , 255 },
	{ 0 , 72 , 255 },
	{ 0 , 67 , 255 },
	{ 0 , 61 , 255 },
	{ 0 , 56 , 255 },
	{ 0 , 50 , 255 },
	{ 0 , 45 , 255 },
	{ 0 , 39 , 255 },
	{ 0 , 34 , 255 },
	{ 0 , 29 , 255 },
	{ 0 , 23 , 255 },
	{ 0 , 18 , 255 },
	{ 0 , 12 , 255 },
	{ 0 , 7 , 255 },
	{ 0 , 1 , 255 },
	{ 3 , 0 , 255 },
	{ 8 , 0 , 255 },
	{ 14 , 0 , 255 },
	{ 19 , 0 , 255 },
	{ 25 , 0 , 255 },
	{ 30 , 0 , 255 },
	{ 36 , 0 , 255 },
	{ 41 , 0 , 255 },
	{ 47 , 0 , 255 },
	{ 52 , 0 , 255 },
	{ 57 , 0 , 255 },
	{ 63 , 0 , 255 },
	{ 68 , 0 , 255 },
	{ 74 , 0 , 255 },
	{ 79 , 0 , 255 },
	{ 85 , 0 , 255 },
	{ 90 , 0 , 255 },
	{ 95 , 0 , 255 },
	{ 101 , 0 , 255 },
	{ 106 , 0 , 255 },
	{ 112 , 0 , 255 },
	{ 117 , 0 , 255 },
	{ 123 , 0 , 255 },
	{ 128 , 0 , 255 },
	{ 133 , 0 , 255 },
	{ 139 , 0 , 255 },
	{ 144 , 0 , 255 },
	{ 150 , 0 , 255 },
	{ 155 , 0 , 255 },
	{ 161 , 0 , 255 },
	{ 166 , 0 , 255 },
	{ 172 , 0 , 255 },
	{ 177 , 0 , 255 },
	{ 182 , 0 , 255 },
	{ 188 , 0 , 255 },
	{ 193 , 0 , 255 },
	{ 199 , 0 , 255 },
	{ 204 , 0 , 255 },
	{ 210 , 0 , 255 },
	{ 215 , 0 , 255 },
	{ 220 , 0 , 255 },
	{ 226 , 0 , 255 },
	{ 231 , 0 , 255 },
	{ 237 , 0 , 255 },
	{ 242 , 0 , 255 },
	{ 248 , 0 , 255 },
	{ 253 , 0 , 255 },
	{ 255 , 0 , 251 },
	{ 255 , 0 , 245 },
	{ 255 , 0 , 240 },
	{ 255 , 0 , 234 },
	{ 255 , 0 , 229 },
	{ 255 , 0 , 223 },
	{ 255 , 0 , 218 },
	{ 255 , 0 , 212 },
	{ 255 , 0 , 207 },
	{ 255 , 0 , 202 },
	{ 255 , 0 , 196 },
	{ 255 , 0 , 191 } };
	const std::vector<std::string> GIST_RAINBOW{
		"ff0028",
		"ff0023",
		"ff001e",
		"ff0018",
		"ff0013",
		"ff000e",
		"ff0008",
		"ff0003",
		"ff0100",
		"ff0700",
		"ff0c00",
		"ff1200",
		"ff1700",
		"ff1c00",
		"ff2200",
		"ff2700",
		"ff2d00",
		"ff3200",
		"ff3700",
		"ff3d00",
		"ff4200",
		"ff4800",
		"ff4d00",
		"ff5200",
		"ff5800",
		"ff5d00",
		"ff6300",
		"ff6800",
		"ff6e00",
		"ff7300",
		"ff7800",
		"ff7e00",
		"ff8300",
		"ff8900",
		"ff8e00",
		"ff9300",
		"ff9900",
		"ff9e00",
		"ffa400",
		"ffa900",
		"ffae00",
		"ffb400",
		"ffb900",
		"ffbf00",
		"ffc400",
		"ffc900",
		"ffcf00",
		"ffd400",
		"ffda00",
		"ffdf00",
		"ffe400",
		"ffea00",
		"ffef00",
		"fff500",
		"fffa00",
		"feff00",
		"f8ff00",
		"f3ff00",
		"edff00",
		"e8ff00",
		"e3ff00",
		"ddff00",
		"d8ff00",
		"d2ff00",
		"cdff00",
		"c7ff00",
		"c2ff00",
		"bdff00",
		"b7ff00",
		"b2ff00",
		"acff00",
		"a7ff00",
		"a2ff00",
		"9cff00",
		"97ff00",
		"91ff00",
		"8cff00",
		"87ff00",
		"81ff00",
		"7cff00",
		"76ff00",
		"71ff00",
		"6cff00",
		"66ff00",
		"61ff00",
		"5bff00",
		"56ff00",
		"51ff00",
		"4bff00",
		"46ff00",
		"40ff00",
		"3bff00",
		"36ff00",
		"30ff00",
		"2bff00",
		"25ff00",
		"20ff00",
		"1bff00",
		"15ff00",
		"10ff00",
		"0aff00",
		"05ff00",
		"00ff00",
		"00ff05",
		"00ff0a",
		"00ff10",
		"00ff15",
		"00ff1a",
		"00ff20",
		"00ff25",
		"00ff2b",
		"00ff30",
		"00ff35",
		"00ff3b",
		"00ff40",
		"00ff45",
		"00ff4b",
		"00ff50",
		"00ff56",
		"00ff5b",
		"00ff60",
		"00ff66",
		"00ff6b",
		"00ff70",
		"00ff76",
		"00ff7b",
		"00ff81",
		"00ff86",
		"00ff8b",
		"00ff91",
		"00ff96",
		"00ff9b",
		"00ffa1",
		"00ffa6",
		"00ffac",
		"00ffb1",
		"00ffb6",
		"00ffbc",
		"00ffc1",
		"00ffc6",
		"00ffcc",
		"00ffd1",
		"00ffd7",
		"00ffdc",
		"00ffe1",
		"00ffe7",
		"00ffec",
		"00fff1",
		"00fff7",
		"00fffc",
		"00fbff",
		"00f6ff",
		"00f1ff",
		"00ebff",
		"00e6ff",
		"00e0ff",
		"00dbff",
		"00d5ff",
		"00d0ff",
		"00caff",
		"00c5ff",
		"00c0ff",
		"00baff",
		"00b5ff",
		"00afff",
		"00aaff",
		"00a4ff",
		"009fff",
		"009aff",
		"0094ff",
		"008fff",
		"0089ff",
		"0084ff",
		"007eff",
		"0079ff",
		"0074ff",
		"006eff",
		"0069ff",
		"0063ff",
		"005eff",
		"0058ff",
		"0053ff",
		"004dff",
		"0048ff",
		"0043ff",
		"003dff",
		"0038ff",
		"0032ff",
		"002dff",
		"0027ff",
		"0022ff",
		"001dff",
		"0017ff",
		"0012ff",
		"000cff",
		"0007ff",
		"0001ff",
		"0300ff",
		"0800ff",
		"0e00ff",
		"1300ff",
		"1900ff",
		"1e00ff",
		"2400ff",
		"2900ff",
		"2f00ff",
		"3400ff",
		"3900ff",
		"3f00ff",
		"4400ff",
		"4a00ff",
		"4f00ff",
		"5500ff",
		"5a00ff",
		"5f00ff",
		"6500ff",
		"6a00ff",
		"7000ff",
		"7500ff",
		"7b00ff",
		"8000ff",
		"8500ff",
		"8b00ff",
		"9000ff",
		"9600ff",
		"9b00ff",
		"a100ff",
		"a600ff",
		"ac00ff",
		"b100ff",
		"b600ff",
		"bc00ff",
		"c100ff",
		"c700ff",
		"cc00ff",
		"d200ff",
		"d700ff",
		"dc00ff",
		"e200ff",
		"e700ff",
		"ed00ff",
		"f200ff",
		"f800ff",
		"fd00ff",
		"ff00fb",
		"ff00f5",
		"ff00f0",
		"ff00ea",
		"ff00e5",
		"ff00df",
		"ff00da",
		"ff00d4",
		"ff00cf",
		"ff00ca",
		"ff00c4",
		"ff00bf"
	};
