#include "misc_helpers.hpp"

void custom_helpers::print_to_console(const char* text) {
	if (text == nullptr) return;
	interfaces::console->console_printf(text);
}

void custom_helpers::state_to_console(const char* tag,  const char* text) {
	if (text == nullptr || tag == nullptr) return;
	interfaces::console->console_printf("[NullHooks] [%s] %s\n", tag, text);
}

void custom_helpers::state_to_console_color(const char* tag, const char* text) {
	if (text == nullptr || tag == nullptr) return;
	
	// ???
	interfaces::console->console_color_printf(color::red(255), "[NullHooks] [%s] %s\n", tag, text);
	interfaces::console->console_color_printf(color::blue(255), "[NullHooks] [%s] %s\n", tag, text);
	interfaces::console->console_color_printf(color::green(255), "[NullHooks] [%s] %s\n", tag, text);
}

color custom_helpers::hsv2color(float H, float S, float V) {
    color col;
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    } else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    } else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    } else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    } else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }
    col.r = (r + m) * 255;
    col.g = (g + m) * 255;
    col.b = (b + m) * 255;
    col.a = 255;
    return col;
}

vec3_t custom_helpers::hsv_float2color2(float H) {
	vec3_t col;
	float v = 1 / 100;
	float C = 0.1 * 0.1;
	float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (H >= 0 && H < 60)
		r = C, g = X, b = 0;
	else if (H >= 60 && H < 120)
		r = X, g = C, b = 0;
	else if (H >= 120 && H < 180)
		r = 0, g = C, b = X;
	else if (H >= 180 && H < 240)
		r = 0, g = X, b = C;
	else if (H >= 240 && H < 300)
		r = X, g = 0, b = C;
	else
		r = C, g = 0, b = X;
	
	col.x = (r + m);
	col.y = (g + m);
	col.z = (b + m);
	return col;
}

color custom_helpers::hsv_float2color(float hue, float saturation, float brightness) {
	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return color(
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255),
			(unsigned char)(p * 255)
		);
	}
	else if (h < 2)
	{
		return color(
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255)
		);
	}
	else if (h < 3)
	{
		return color(
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255)
		);
	}
	else if (h < 4)
	{
		return color(
			(unsigned char)(p * 255),
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255)
		);
	}
	else if (h < 5)
	{
		return color(
			(unsigned char)(t * 255),
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255)
		);
	}
	else
	{
		return color(
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255),
			(unsigned char)(q * 255)
		);
	}
}

color custom_helpers::int2color(int* id) {
	if (*id < 100)				return color(255, 0, 0);
	else if (*id < 200)			return color(255, 128, 0);
	else if (*id < 300)			return color(255, 255, 0);
	else if (*id < 400)			return color(128, 255, 0);
	else if (*id < 500)			return color(0, 255, 0);
	else if (*id < 600)			return color(0, 255, 128);
	else if (*id < 700)			return color(0, 255, 255);
	else if (*id < 800)			return color(0, 128, 255);
	else if (*id < 900)			return color(0, 0, 255);
	else if (*id < 1000)			return color(128, 0, 255);
	else if (*id < 1100)		return color(255, 0, 255);
	else if (*id < 1200)		return color(255, 0, 128);
	else						*id = 0;

	return color(255, 0, 0);
}

void custom_helpers::draw_bomb_text(float time) {
	char exp_time[64];
	sprintf_s(exp_time, "%.2f", time);

	const std::string exp_time_str_base = "Bomb will explode in: ";
	const std::string exp_time_str = std::string(exp_time);
	const std::string total = exp_time_str_base + exp_time_str;
	const std::wstring c_exp_time_str_base = std::wstring(exp_time_str_base.begin(), exp_time_str_base.end());
	const std::wstring c_exp_time_str = std::wstring(exp_time_str.begin(), exp_time_str.end());
	const std::wstring c_total = std::wstring(total.begin(), total.end());

	const color base_color = color(255, 130, 0, 255);
	const color bomb_color_text_color = (time > 10.f) ? color(255, 190, 0, 255) : color::red(255);

	int screen_width, screen_height;
	interfaces::engine->get_screen_size(screen_width, screen_height);

	int width, height;
	interfaces::surface->draw_text_font(render::fonts::watermark_font);
	interfaces::surface->get_text_size(render::fonts::watermark_font, c_total.c_str(), width, height);
	const int x_pos = screen_width / 2 - width / 2;
	const int y_pos = 80;

	interfaces::surface->draw_text_pos(x_pos, y_pos);

	interfaces::surface->set_text_color(base_color.r, base_color.g, base_color.b, base_color.a);
	interfaces::surface->draw_render_text(c_exp_time_str_base.c_str(), wcslen(c_exp_time_str_base.c_str()));

	interfaces::surface->set_text_color(bomb_color_text_color.r, bomb_color_text_color.g, bomb_color_text_color.b, bomb_color_text_color.a);
	interfaces::surface->draw_render_text(c_exp_time_str.c_str(), wcslen(c_exp_time_str.c_str()));
}