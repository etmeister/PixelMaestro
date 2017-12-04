/*
 * Canvas.h - Base class for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include "../core/colors.h"
#include "../core/point.h"
#include "../core/section.h"
#include "../core/timing/timing.h"
#include "fonts/font.h"
#include "canvastype.h"

namespace PixelMaestro {
	class Section;
	class Timing;

	class Canvas {
		public:
			// Virtual functions - must be implemented in derived Canvases.
			virtual ~Canvas();
			virtual void activate(uint16_t x, uint16_t y) = 0;
			virtual void deactivate(uint16_t x, uint16_t y) = 0;
			virtual Colors::RGB get_pixel_color(uint16_t x, uint16_t y) = 0;
			virtual CanvasType::Type get_type() = 0;
			virtual void initialize() = 0;

			Canvas(Section* section);
			Canvas(Section* section, uint16_t num_frames);
			void clear();
			void draw_circle(uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_line(uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(uint16_t x, uint16_t y);
			void draw_rect(uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars);
			void draw_triangle(uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			void erase(uint16_t x, uint16_t y);
			uint16_t get_current_frame_index();
			Timing* get_frame_timing();
			uint16_t get_num_frames();
			Section* get_section();
			bool in_bounds(uint16_t x, uint16_t y);
			void next_frame();
			void remove_frame_timing();
			void set_current_frame_index(uint16_t index);
			void set_frame_timing(uint16_t speed);
			void set_num_frames(uint16_t num_frames);
			void set_offset(int16_t x, int16_t y);
			void set_section(Section* section_);
			void update(const uint32_t& current_time);

		protected:
			/// The index of the current frame.
			uint16_t current_frame_index_ = 0;

			/// Controls timings for frame animations.
			Timing* frame_timing_ = nullptr;

			/// The number of frames.
			uint16_t num_frames_ = 0;

			/**
			 * The Canvas' parent Section.
			 * This is automatically set after using Section::set_canvas().
			 */
			Section* section_ = nullptr;

			virtual void delete_frames() = 0;
	};
}

#endif // CANVAS_H
