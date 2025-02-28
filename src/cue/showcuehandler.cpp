#include "showcuehandler.h"

namespace PixelMaestro {

	uint8_t* ShowCueHandler::set_events(Event *events, uint16_t num_events, bool preserve_current_index) {

		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::ShowCueHandler,
			(uint8_t)Action::SetEvents
		);
		add_uint16_to_cue(index, num_events);
		controller_.get_buffer()[++index] = (uint8_t)preserve_current_index;

		for (uint16_t event_index = 0; event_index < num_events; event_index++) {
			// Save time
			add_uint32_to_cue(index, events[event_index].get_time());

			// Save Cue
			uint8_t* event_cue = events[event_index].get_cue();
			uint32_t cue_size = controller_.get_cue_size(event_cue);
			for (uint32_t cue_index = 0; cue_index < cue_size; cue_index++) {
				controller_.get_buffer()[++index] = event_cue[cue_index];
			}
		}

		return controller_.assemble(++index);
	}

	uint8_t* ShowCueHandler::set_looping(bool loop) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::ShowCueHandler,
			(uint8_t)Action::SetLooping
		);
		controller_.get_buffer()[++index] = (uint8_t)loop;

		return controller_.assemble(++index);
	}

	uint8_t* ShowCueHandler::set_timing_mode(Show::TimingMode timing) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::ShowCueHandler,
			(uint8_t)Action::SetTimingMode
		);
		controller_.get_buffer()[++index] = (uint8_t)timing;

		return controller_.assemble(++index);
	}

	void ShowCueHandler::run(uint8_t *cue) {
		Show* show = controller_.get_maestro().get_show();

		if (show == nullptr) return;

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::SetEvents:
				{
					// Delete existing Events
					delete [] show->get_events();
					uint16_t num_events = IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]);
					bool preserve_cycle_index = cue[(uint8_t)Byte::OptionsByte + 2];

					// Rebuild Event list
					Event* events = new Event[num_events];
					uint32_t options_index = (uint8_t)Byte::OptionsByte + 3;
					for (uint16_t event = 0; event < num_events; event++) {
						// Set time
						uint32_t time = IntByteConvert::byte_to_uint32(&cue[options_index]);
						events[event].set_time(time);

						// Skip past the cue time to get the cue itself
						options_index += 4;

						// Set Cues
						uint16_t event_cue_size = controller_.get_cue_size(&cue[options_index]);
						events[event].set_cue(&cue[options_index]);
						options_index += event_cue_size;
					}

					show->set_events(events, num_events, preserve_cycle_index);
				}
				break;
			case Action::SetLooping:
				show->set_looping((bool)cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetTimingMode:
				show->set_timing_mode((Show::TimingMode)cue[(uint8_t)Byte::OptionsByte]);
				break;
		}
	}
}
