#ifndef FIREANIMATION_H
#define FIREANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class FireAnimation : public MappedAnimation {
		public:
			explicit FireAnimation(Section* section);
			~FireAnimation();
			uint8_t get_multiplier() const;
			void map();
			void set_multiplier(uint8_t multiplier);
			void update();

		private:
			/// Sets the size of the flames (larger value = bigger flames).
			uint8_t multiplier_ = 48;
	};
}

#endif // FIREANIMATION_H