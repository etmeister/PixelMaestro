#include "presetdemo.h"
#include "preset/demopreset.h"

PresetDemo::PresetDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(60, 10));

	// Applies the Preset, then clears it from memory afterwards.
	maestro_controller_->get_maestro()->apply_preset(new DemoPreset(), true);
}

PresetDemo::~PresetDemo() {
}
