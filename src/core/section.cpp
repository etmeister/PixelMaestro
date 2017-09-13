/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include "../utility.h"
#include "colors.h"
#include "pixel.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Assigns Pixels to the Section.
	 * @param layout Initial layout (rows and columns) of the Pixels.
	 */
	Section::Section(Point* layout) {
		set_pixels(layout);
	}

	/**
	 * Creates a new Canvas with the dimensions of the array.
	 * @return New Canvas.
	 */
	Canvas* Section::add_canvas() {
		if (canvas_ == nullptr) {
			canvas_ = new Canvas(this);
		}
		return canvas_;
	}

	/**
		Returns the current animation.

		@return Current animation.
	*/
	Animation* Section::get_animation() {
		return animation_;
	}

	/**
	 * Returns the Section's Canvas.
	 * @return Section's Canvas.
	 */
	Canvas* Section::get_canvas() {
		return canvas_;
	}

	/**
		Returns the amount of time between animation changes.

		@return speed The amount of time between animation changes.
	*/
	unsigned short Section::get_cycle_interval() {
		return cycle_interval_;
	}

	/**
		Returns the size of the Pixel grid.

		@return Size of the Pixel grid.
	*/
	Point* Section::get_dimensions() {
		return dimensions_;
	}

	/**
	 * Returns the Overlay (if one exists).
	 *
	 * @return Active Overlay.
	 */
	Section::Overlay* Section::get_overlay() {
		return overlay_;
	}

	/**
		Returns the Pixel at the specified index.

		@param pixel The index of the Pixel in the pixels_ array.
	*/
	Pixel* Section::get_pixel(unsigned int pixel) {
		return &pixels_[pixel];
	}

	/**
		Returns the final color of the specified Pixel after applying post-processing effects (e.g. Overlays).

		@param pixel Index of the Pixel.
		@return RGB value of the Pixel's final color.
	*/
	Colors::RGB Section::get_pixel_color(unsigned int pixel) {
		if (overlay_ != nullptr) {
			return Colors::mix_colors(get_pixel(pixel)->get_color(), overlay_->section->get_pixel(pixel)->get_color(), overlay_->mix_mode, overlay_->alpha);
		}
		else {
			return *get_pixel(pixel)->get_color();
		}
	}

	/**
	 * Returns the index of a Pixel given the Pixel's Point.
	 * @param coordinates The Pixel's Point.
	 * @return The index of the Pixel.
	 */
	unsigned int Section::get_pixel_index(Point* coordinates) {
		return get_pixel_index(coordinates->x, coordinates->y);
	}

	/**
		Returns the index of a Pixel given the x and y-coordinates.

		@param x The Pixel's x-coordinate.
		@param y The Pixel's y-coordinate.
		@return The index of the Pixel.
	*/
	unsigned int Section::get_pixel_index(unsigned short x, unsigned short y) {
		return (y * dimensions_->x) + x;
	}

	/**
		Returns the Section's refresh rate.

		@return The refresh rate of the Section.
	*/
	unsigned short Section::get_refresh_interval() {
		return refresh_interval_;
	}

	/**
		Sets all Pixels to the specified color.

		@param color New color.
	*/
	void Section::set_all(Colors::RGB* color) {
		for (unsigned int pixel = 0; pixel < dimensions_->size(); pixel++) {
			set_one(pixel, color);
		}
	}

	/**
		Changes the current animation.

		@param animation New animation.
		@param preserve_cycle_index If true, resume from the cycle_index of the previous animation.
	*/
	void Section::set_animation(Animation* animation, bool preserve_cycle_index) {
		if (preserve_cycle_index && animation_) {
			animation->set_cycle_index(animation_->get_cycle_index());
		}

		animation_ = animation;
	}

	/**
		Sets the Canvas to display.
		Also sets the Canvas' parent Section to the current Section.

		@param canvas New Canvas.
	*/
	void Section::set_canvas(Canvas* canvas) {
		canvas_ = canvas;
		canvas_->parent_section = this;
	}

	/**
		Sets the speed between animation cycles.

		@param interval Time between animation cycles (in milliseconds).
		@param pause Time to delay the start of the transition to the next animation (in ms).
	*/
	void Section::set_cycle_interval(unsigned short interval, unsigned short pause) {
		cycle_interval_ = interval;
		pause_ = pause;
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel The index of the Pixel to update.
		@param color New color.
	*/
	void Section::set_one(unsigned int pixel, Colors::RGB* color) {
		// Only continue if Pixel is within the bounds of the array.
		if (pixel < dimensions_->size()) {
			/*
				If pause is enabled, trick the Pixel into thinking the cycle is shorter than it is.
				This results in the Pixel finishing early and waiting until the next cycle.
			*/
			if (pause_ > 0) {
				get_pixel(pixel)->set_next_color(color, animation_->get_fade(), cycle_interval_ - pause_, refresh_interval_);
			}
			else {
				get_pixel(pixel)->set_next_color(color, animation_->get_fade(), cycle_interval_, refresh_interval_);
			}
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param x The column number of the Pixel.
		@param y The row number of the Pixel.
		@param color New color.
	*/
	void Section::set_one(unsigned short x, unsigned short y, Colors::RGB* color) {
		set_one(get_pixel_index(x, y), color);
	}

	/**
		Overlays another  Section on top of the current Section.
		You can retrieve the blended output by using get_pixel_color() on the base Section.

		@param overlay The Overlay to set.
	*/
	void Section::set_overlay(Overlay* overlay) {
		overlay_ = overlay;
	}

	/**
		Sets the Pixel array and layout used in the Section.

		@param dimensions Dimensions of the Pixel array.
	*/
	void Section::set_pixels(Point* dimensions) {
		// Resize the Pixel grid
		if (pixels_ != nullptr) {
			delete pixels_;
		}

		// Resize the Canvas while preserving as much data as possible.
		if (canvas_ != nullptr) {
			// Create a temporary array for storing the pattern.
			bool tmp[dimensions_->x * dimensions_->y] = {0};
			for (int pixel = 0; pixel < dimensions_->x * dimensions_->y; pixel++) {
				tmp[pixel] = canvas_->pattern[pixel];
			}
			// Delete the current array, then create a new one and copy back as many of the original values as possible.
			delete canvas_->pattern;

			// Make sure we don't exceed the bounds of either the new grid or the old grid.
			int max = dimensions_->x * dimensions_->y;
			if (dimensions->x * dimensions->y < max) {
				max = dimensions->x * dimensions->y;
			}
			canvas_->pattern = new bool[max];
			for (unsigned int pixel = 0; pixel < (unsigned int)max; pixel++) {
				tmp[pixel] = canvas_->pattern[pixel];
			}
		}

		// Rebuild Pixels
		pixels_ = new Pixel[dimensions->x * dimensions->y];
		dimensions_ = dimensions;
	}

	/**
		Sets the refresh rate of the Section (how quickly the Pixels update).

		@param interval Rate in milliseconds between Pixel redraws.
	*/
	void Section::set_refresh_interval(unsigned short interval) {
		refresh_interval_ = interval;
	}

	/**
		Removes the overlay from the Section.
	*/
	void Section::unset_overlay() {
		overlay_ = nullptr;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Section::update(const unsigned long& current_time) {

		// If no animation is set, do nothing.
		if (this->animation_ == nullptr) {
			return;
		}

		// If this Section has an Overlay, update it first.
		if (overlay_ != nullptr) {
			overlay_->section->update(current_time);
		}

		/*
		 * Refresh the Pixels.
		 * refresh_interval_ tracks the amount of time between Pixel draws, and last_refresh_ tracks the time of the last refresh.
		 */
		if (current_time - last_refresh_ >= (unsigned long)refresh_interval_) {

			/*
				Update the animation cycle.
				cycle_interval_ tracks the amount of time between cycles, while last_cycle_ tracks the time of the last change.
				If it's time for the next cycle, run the animation.
			*/
			if (current_time - last_cycle_ >= (unsigned long)cycle_interval_) {

				// Run the animation.
				animation_->update(this);

				/*
				 * If a Canvas is set, update it.
				 */
				if (canvas_ != nullptr) {
					canvas_->update(current_time);
				}

				// Update the last cycle time.
				last_cycle_ = current_time;
			}

			// Only update each Pixel if we're fading or if the cycle has changed.
			if (animation_->get_fade() || last_cycle_ == current_time) {
				for (unsigned short pixel = 0; pixel < dimensions_->size(); pixel++) {
					get_pixel(pixel)->update();
				}
			}

			// Update the last refresh time.
			last_refresh_ = current_time;
		}
	}

	Section::~Section() {
		if (canvas_ != nullptr) {
			delete canvas_;
		}
		if (pixels_ != nullptr) {
			delete pixels_;
		}
	}
}
