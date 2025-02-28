#include "../canvas/canvas.h"
#ifdef CANVAS_ENABLE_FONTS
#include "../canvas/fonts/font5x8.h"
#endif // CANVAS_ENABLE_FONTS
#include "canvascuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	uint8_t* CanvasCueHandler::clear(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::Clear,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawCircle,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, origin_x);
		add_uint16_to_cue(index, origin_y);
		add_uint16_to_cue(index, radius);
		controller_.get_buffer()[++index] = (uint8_t)fill;

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t frame_index,  uint16_t size_x, uint16_t size_y, const uint8_t* frame) {

		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawFrame,
			section_num,
			layer_num,
			frame_index
		);

		add_uint16_to_cue(index, size_x);
		add_uint16_to_cue(index, size_y);

		Point grid(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				controller_.get_buffer()[++index] = frame[grid.get_inline_index(x, y)];
			}
		}

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_line(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawLine,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, origin_x);
		add_uint16_to_cue(index, origin_y);
		add_uint16_to_cue(index, target_x);
		add_uint16_to_cue(index, target_y);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_point(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t x, uint16_t y) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawPoint,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, x);
		add_uint16_to_cue(index, y);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawRect,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, origin_x);
		add_uint16_to_cue(index, origin_y);
		add_uint16_to_cue(index, size_x);
		add_uint16_to_cue(index, size_y);
		controller_.get_buffer()[++index] = (uint8_t)fill;

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawTriangle,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, point_a_x);
		add_uint16_to_cue(index, point_a_y);
		add_uint16_to_cue(index, point_b_x);
		add_uint16_to_cue(index, point_b_y);
		add_uint16_to_cue(index, point_c_x);
		add_uint16_to_cue(index, point_c_y);
		controller_.get_buffer()[++index] = (uint8_t)fill;

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::draw_text(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::DrawText,
			section_num,
			layer_num,
			frame_index
		);

		controller_.get_buffer()[++index] = color_index;
		add_uint16_to_cue(index, origin_x);
		add_uint16_to_cue(index, origin_y);
		controller_.get_buffer()[++index] = (uint8_t)font;
		controller_.get_buffer()[++index] = num_chars;

		for (uint8_t i = 0; i < num_chars; i++) {
			controller_.get_buffer()[++index] = text[i];
		}

		return controller_.assemble(index);
	}

	uint8_t* CanvasCueHandler::erase_point(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint16_t x, uint16_t y) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::ErasePoint,
			section_num,
			layer_num,
			frame_index
		);

		add_uint16_to_cue(index, x);
		add_uint16_to_cue(index, y);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::next_frame(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::NextFrame,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::previous_frame(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::PreviousFrame,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::remove_frame_timer(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::RemoveFrameTimer,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::set_current_frame_index(uint8_t section_num, uint8_t layer_num, uint16_t frame_index) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::SetCurrentFrameIndex,
			section_num,
			layer_num
		);

		add_uint16_to_cue(index, frame_index);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::set_frame_timer(uint8_t section_num, uint8_t layer_num, uint16_t speed) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::SetFrameTimer,
			section_num,
			layer_num
		);

		add_uint16_to_cue(index, speed);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::set_num_frames(uint8_t section_num, uint8_t layer_num, uint16_t num_frames) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::SetNumFrames,
			section_num,
			layer_num
		);

		add_uint16_to_cue(index, num_frames);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::set_palette(uint8_t section_num, uint8_t layer_num, const Palette& palette) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::SetPalette,
			section_num,
			layer_num
		);

		controller_.get_buffer()[++index] = palette.get_num_colors();

		uint16_t palette_size = serialize_palette(&controller_.get_buffer()[++index], palette);

		return controller_.assemble(index + palette_size);
	}

	uint32_t CanvasCueHandler::start_cue(uint8_t handler_byte, uint8_t action_byte, uint8_t section_num, uint8_t layer_num, uint16_t frame_num) {
		uint32_t index = CueHandler::start_cue(handler_byte, action_byte, section_num, layer_num);

		add_uint16_to_cue(index, frame_num);

		return index;
	}

	uint8_t* CanvasCueHandler::start_frame_timer(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::StartFrameTimer,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* CanvasCueHandler::stop_frame_timer(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = CanvasCueHandler::start_cue(
			(uint8_t)CueController::Handler::CanvasCueHandler,
			(uint8_t)Action::StopFrameTimer,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

#ifdef CANVAS_ENABLE_FONTS
	Font* CanvasCueHandler::get_font(Font::Type font_type) {
		Font* font = nullptr;

		switch (font_type) {
			case Font::Type::Font5x8:
				font = new Font5x8();
				break;
		}
		return font;
	}
#endif // #ifdef CANVAS_ENABLE_FONTS

	void CanvasCueHandler::run(uint8_t *cue) {
		Section* section = get_section(cue[(uint8_t)Byte::SectionByte], cue[(uint8_t)Byte::LayerByte]);

		if (section == nullptr) return;

		Canvas* canvas = section->get_canvas();
		if (canvas == nullptr) return;

		uint16_t frame_index = IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::FrameByte1]);

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::Clear:
				canvas->clear();
				break;
			case Action::DrawCircle:
				canvas->draw_circle(
					frame_index,
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 5]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 7]);
				break;
			case Action::DrawFrame:
				{
					Point frame_bounds(
						IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]),
						IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 2])
					);

					for (uint16_t y = 0; y < frame_bounds.y; y++) {
						for (uint16_t x = 0; x < frame_bounds.x; x++) {
							if (canvas->get_section().get_dimensions().in_bounds(x, y)) {
								canvas->draw_point(
									frame_index,
									cue[(uint8_t)Byte::OptionsByte + 4 + frame_bounds.get_inline_index(x, y)], x, y);
							}
						}
					}
				}
				break;
			case Action::DrawLine:
				canvas->draw_line(
					frame_index,
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 7]));
				break;
			case Action::DrawPoint:
				canvas->draw_point(
					frame_index,
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]));
				break;
			case Action::DrawRect:
				canvas->draw_rect(
					frame_index,
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 7]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 9]);
				break;
			case Action::DrawText:
				#ifdef CANVAS_ENABLE_FONTS
				{
					Font* font = get_font((Font::Type)cue[(uint8_t)Byte::OptionsByte + 5]);

					canvas->draw_text(
						frame_index,
						cue[(uint8_t)Byte::OptionsByte],
						IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
						IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]),
						*font,
						(char*)&cue[(uint8_t)Byte::OptionsByte + 7],
						cue[(uint8_t)Byte::OptionsByte + 6]
					);

					delete font;
				}
#endif //#ifdef CANVAS_ENABLE_FONTS
				break;
			case Action::DrawTriangle:
				canvas->draw_triangle(
					frame_index,
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 7]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 9]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 11]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 13]);
				break;
			case Action::ErasePoint:
				canvas->erase_point(
					frame_index,
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 2])
				);
				break;
			case Action::NextFrame:
				canvas->next_frame();
				break;
			case Action::PreviousFrame:
				canvas->previous_frame();
				break;
			case Action::RemoveFrameTimer:
				canvas->remove_frame_timer();
				break;
			case Action::SetCurrentFrameIndex:
				canvas->set_current_frame_index(IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetFrameTimer:
				canvas->set_frame_timer(IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetNumFrames:
				canvas->set_num_frames(IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetPalette:
				{
					uint8_t num_colors = cue[(uint8_t)Byte::OptionsByte];

					// Delete the old Palette after setting the new one.
					Palette* old_palette = canvas->get_palette();
					canvas->set_palette(*deserialize_palette(&cue[(uint8_t)Byte::OptionsByte + 1], num_colors));
					delete old_palette;
				}
				break;
			case Action::StartFrameTimer:
				if (canvas->get_frame_timer()) {
					canvas->get_frame_timer()->start();
				}
				break;
			case Action::StopFrameTimer:
				if (canvas->get_frame_timer()) {
					canvas->get_frame_timer()->stop();
				}
				break;
			default:
				break;
		}
	}
}
