#include "cuecontroller.h"
#include "maestrocuehandler.h"
#include "showcuehandler.h"

namespace PixelMaestro {
	uint8_t* MaestroCueHandler::set_show(Event *events, uint16_t num_events, bool preserve_event_index) {
		// TODO: This doesn't seem right. Review this.
		bool has_events = (events != nullptr && num_events > 0);
		if (has_events) {
			static_cast<ShowCueHandler*>(controller_->get_handler(CueController::Handler::ShowHandler))->set_events(events, num_events, preserve_event_index);
		}

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::SetShow;

		if (!has_events) {
			return controller_->assemble(Byte::OptionsByte);
		}
		else {
			return controller_->get_buffer();
		}
	}

	uint8_t* MaestroCueHandler::set_timing(uint16_t interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::SetTiming;
		controller_->get_buffer()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = interval_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 2));
	}

	uint8_t* MaestroCueHandler::sync(const uint32_t new_time) {
		IntByteConvert last_time_byte(new_time);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::Sync;
		controller_->get_buffer()[Byte::OptionsByte] = last_time_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = last_time_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 2));
	}

	void MaestroCueHandler::run(uint8_t *cue) {
		switch((Action)cue[MaestroCueHandler::Byte::ActionByte]) {
			case Action::SetShow:
				{
					// Initialize the Show in two steps
					controller_->get_maestro()->set_show(nullptr, 0);

					// TODO: Initialize Events
				}
				break;
			case Action::SetTiming:
				{
					uint32_t interval = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]);
					controller_->get_maestro()->set_timing(interval);
				}
				break;
			case Action::Sync:
				{
					uint32_t new_time = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]);
					controller_->get_maestro()->sync(new_time);
				}
				break;
		}
	}

	MaestroCueHandler::~MaestroCueHandler() { }
}
