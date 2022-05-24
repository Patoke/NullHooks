#include "../features.hpp"

void visuals::noflash() {
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;
	if (!csgo::local_player) return;

	if (!variables::misc_visuals::noflash) {
		if (csgo::local_player->flash_alpha() < 255.f)
			csgo::local_player->flash_alpha() = 255.f;
		return;
	}

	// TODO: Add slider for intensity?
	if (csgo::local_player->flash_alpha() > 0.f)
		csgo::local_player->flash_alpha() = 0.f;
}
