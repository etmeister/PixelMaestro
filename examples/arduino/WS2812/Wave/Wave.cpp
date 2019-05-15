/*
 * Wave.cpp - Creates an 8 LED strip and displays a Wave animation.
 * Change LED_PIN to the pin that your strip is attached to.
 */

#include <Arduino.h>
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <colorpresets.h>
#include <WS2812.h>
#include <cRGB.h>

using namespace PixelMaestro;

// Create a Maestro with a Section 8 pixels wide and 1 pixel high
Maestro maestro(8, 1);
Section& section = maestro.get_section(0);

// Initialize WS1812 components
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(section.get_dimensions().size());

// Translate PixelMaestro RGB to LightWS2812 cRGB
cRGB RGBtoCRGB(Colors::RGB rgb) {
	return cRGB {
		rgb.r,
		rgb.g,
		rgb.b
	};
}

void setup () {
	ws.setOutput(LED_PIN);

	// Set global brightness to 10%
	maestro.set_brightness(25);

	// Create a new wave animation, change the palette to ColorWheel, then set the speed to 500ms.
	Animation& animation = section.set_animation(AnimationType::Wave);
	animation.set_palette(ColorPresets::Colorwheel_Palette);
	animation.set_timer(500);
}

void loop() {
	if (maestro.update(millis())) {
		uint8_t led = 0;
		for (uint8_t y = 0; y < section.get_dimensions().y; y++) {
			for (uint8_t x = 0; x < section.get_dimensions().x; x++) {
				ws.set_crgb_at(led, RGBtoCRGB(section.get_pixel_color(x, y)));
				led++;
			}
		}

		ws.sync();
	}
}
