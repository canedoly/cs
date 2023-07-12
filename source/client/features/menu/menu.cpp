#include "menu.h"

#include "../../hooks/hooks.h"
#include "../../include/math.h"
#include "../../include/util.h"
#include <fstream>
#include <string>
#include "../../include/json.h"
#include "../visuals/visuals.h"

void c_menu::press_sound() {
	//why not
	//shouldnt we use isurface playsound for this?
	ctx->m_surface->play_sound("ui/buttonclick.wav");
}

void c_menu::render_window(std::string label, rect_t size, color background, color edge) {
	//background
	//ctx->m_surface->draw_set_alpha( 1.0f );
	render->filled_rect(size.m_x, size.m_y, size.m_w, size.m_h, background);

	if (config->m_menu.m_skull_background) {
		static int texture = render->create_array_texture(textures::skull::raw_data, textures::skull::width, textures::skull::height);
		render->draw_texture_rect(size.m_x, size.m_y + 25, textures::skull::width, textures::skull::height, texture, color(255, 255, 255, 5));
	}

	render->outlined_text(size.m_x + size.m_w / 2, size.m_y + 1, ALIGN_CENTERHORIZONTAL, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.outlined_string( ESP, size.m_x + size.m_w / 2, size.m_y + 1, { 255, 255, 255, 255 }, ALIGN_CENTERHORIZONTAL, label.c_str( ) );
	render->outlined_rect(size.m_x, size.m_y, size.m_w, size.m_h, edge);
	render->line(size.m_x, size.m_y + 15, size.m_x + size.m_w, size.m_y + 15, edge);
	render->line(size.m_x, size.m_y + 35, size.m_x + size.m_w, size.m_y + 35, edge);
	//ctx->m_surface->draw_set_alpha( m_fade_alpha );
	//render->outlined_text( size.m_x + size.m_w - 5, size.m_y + 1, ALIGN_RIGHT, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "Registered to: %s", ctx->m_user_name.c_str( ) );
}

bool c_menu::menu_tab(std::string label, bool active) {
	int x = m_last_tab.m_x;
	int y = m_last_tab.m_y;
	int w = m_last_tab.m_w;
	int h = m_last_tab.m_h;

	bool callback = false;

	if (input->in_area(x, y, w - 1, h)) {
		if (input->is_pressed(VK_LBUTTON)) {
			press_sound();
			callback = true;
		}

		if (!active)
			render->filled_rect(x + 1, y + 1, w - 1, h - 1, color(64, 64, 64));
	}

	if (active)
		render->filled_rect(x, y + 1, w + 2, h - 1, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));

	render->outlined_text(x + (w * 0.5f), y + (h * 0.5f), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.line( x + w, y, x + w, y + h, config->m_colors.m_ui_accent );

	m_last_tab.m_x = x + w;

	return callback;
}

bool c_menu::menu_subtab(std::string label, bool active) {
	int x = m_last_subtab.m_x;
	int y = m_last_subtab.m_y;
	int w = m_last_subtab.m_w;
	int h = m_last_subtab.m_h;

	bool callback = false;

	if (input->in_area(x, y, w - 1, h)) {
		if (input->is_pressed(VK_LBUTTON)) {
			press_sound();
			callback = true;
		}

		if (!active)
			render->filled_rect(x + 1, y + 1, w - 2, h - 1, color(64, 64, 64));
	}

	if (active)
		render->filled_rect(x - 1, y + 1, w + 2, h - 1, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));

	render->outlined_text(x + (w * 0.5f), y + 8, ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.line( x + w, y, x + w, y + h, config->m_colors.m_ui_accent );

	m_last_subtab.m_x = x + w;

	return callback;
}

void c_menu::menu_group_start(bool right, bool up, bool subtab) {
	m_last_group.m_x = (right ? m_window.m_x + 220 + 10 + 1 : m_last_group.m_x);
	last_group_y = (up ? m_window.m_y + 40 : m_last_group.m_y + 2);
	m_last_group.m_y = (up ? m_window.m_y + 50 : m_last_group.m_y + 12);

	if (subtab) {
		last_group_y += 15;
		m_last_group.m_y += 15;
	}
}

void c_menu::menu_group(std::string label) {
	int x = m_last_group.m_x;
	int y = last_group_y + 1;
	int w = m_last_group.m_w;
	int h = m_last_group.m_y - last_group_y;

	/*if ( h > 195 )
	{
		h -= ( ( m_last_group.m_y - last_group_y ) - 195 );
	}*/

	//draw.line( x, y + custom_y, x + w, y + custom_y, config->m_colors.m_ui_accent );
	render->outlined_rect(x, y, w, h, config->m_colors.m_ui_accent);

	int text_w, text_h;
	ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(label.c_str()).c_str(), text_w, text_h);

	render->line(x + (w / 2) - (text_w / 2) - 5, y, x + (w / 2) + (text_w / 2) + 6, y, config->m_colors.m_ui_background);
	render->outlined_text(x + (w / 2) + 1, y + 1, ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, { 255, 255, 255, 255 }, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTER, label.c_str( ) );

	m_last_group.m_x = x;
	m_last_group.m_y = y + text_h + h - 10;
}

bool c_menu::button(std::string label, std::function<void()> callback_func) {
	bool callback = false;

	int x = m_last_group.m_x;
	int y = m_last_group.m_y - 5;
	int w = 90;
	int h = 15;

	float time_pressed = 0.0f;

	if (input->in_area(x, y, w, h) && !m_combobox_open && !m_multi_combobox_open) {
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));
	}
	else {
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	render->outlined_text(x + (w / 2) + 5, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());

	if (input->in_area(x, y, w, h) && !m_combobox_open && !m_multi_combobox_open)
	{
		float time = ctx->m_engine_client->time();
		if (input->is_pressed(VK_LBUTTON))
		{
			callback_func();
			callback = true;
			time_pressed = time;
			press_sound();
		}
		else if (time > time_pressed + 0.1f)
		{
			time_pressed = 0.0f;
		}
	}
	else
	{
		time_pressed = 0.0f;
	}

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 10;

	return callback;
}

bool c_menu::check_box(std::string label, bool& var) {
	int x = m_last_group.m_x;
	int y = m_last_group.m_y;
	int w = 10;
	int h = 10;
	bool callback = false;

	render->outlined_rect(x + 5, y - 5, w, h, config->m_colors.m_ui_accent);

	if (input->in_area(x + 5, y - 5, w, h) && !m_combobox_open && !m_multi_combobox_open) {
		render->filled_rect(x + 6, y - 4, w - 2, h - 2, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));
		if (input->is_pressed(VK_LBUTTON)) {
			var = !var;
			callback = true;
			press_sound();
		}
	}

	else {
		render->filled_rect(x + 5, y - 5, w, h, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y - 5, w, h, config->m_colors.m_ui_foreground);
	}

	if (var)
		render->filled_rect(x + 6, y - 4, w - 2, h - 2, config->m_colors.m_ui_accent);

	render->outlined_text(x + w + 5 + 5, y - 1 - 5, ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_DEFAULT, label.c_str( ) );

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 5;

	return callback;
}

bool c_menu::slider_int(std::string label, int& var, int min, int max, int step, const char* format) {
	int x = m_last_group.m_x;
	int y = m_last_group.m_y + 7;
	int w = 210;
	int h = 7;

	bool callback = false;

	render->outlined_text(x + 5, y - 13, ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_DEFAULT, label.c_str( ) );

	render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
	auto fraction = math::remap_val_clamped((float)var / step * step, min, max, 0.0f, 1.0f);

	int sliderx = (fraction * w) + 1;
	if (sliderx > w - 1)
		sliderx = w - 1;

	render->filled_rect(x + 1 + 5, y + 1, sliderx - 1, h - 2, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));

	if (input->in_area((x + 5), y, w, h) && !m_combobox_open && !m_multi_combobox_open) {
		if (input->is_pressed(VK_LBUTTON)) {
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
		else if (input->is_held(VK_LBUTTON)) {
			float fraction = (float)(input->mouse_x - (x + 5)) / w;
			fraction = std::clamp(fraction, 0.0f, 1.0f);

			int newval = (int)(fraction * (max - min)) / step * step + min;
			if (newval != var) {
				var = newval;
				callback = true;
			}
			//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTERHORIZONTAL, "%i", var );
		}

		int textx = std::clamp(x + sliderx + 6, x + 5, x + w);
		render->outlined_text(x + w + 5, y - 13, ALIGN_RIGHT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, format, var);

		render->filled_rect(x + sliderx + 4, y - 1, 3, 9, color(152, 50, 1));
		render->outlined_rect(x + sliderx + 3, y - 2, 5, 11, config->m_colors.m_ui_accent);
	}

	else {
		render->filled_rect(x + 5, y, w, h, config->m_colors.m_ui_background);
		render->filled_rect(x + sliderx + 5, y + 1, w - sliderx - 1, h - 2, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 7;

	return callback;
}

bool c_menu::slider_float(std::string label, float& var, float min, float max, float step, const char* format) {
	int x = m_last_group.m_x;
	int y = m_last_group.m_y + 7;
	int w = 210;
	int h = 7;

	bool callback = false;

	render->outlined_text(x + 5, y - 13, ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_DEFAULT, label.c_str( ) );

	render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
	auto fraction = math::remap_val_clamped((float)var / (1 / step) * (1 / step), min, max, 0.0f, 1.0f);

	int sliderx = (fraction * w) + 1;
	if (sliderx > w - 1)
		sliderx = w - 1;

	render->filled_rect(x + 1 + 5, y + 1, sliderx - 1, h - 2, color(config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80));

	if (input->in_area((x + 5), y, w, h) && !m_combobox_open && !m_multi_combobox_open) {
		if (input->is_pressed(VK_LBUTTON)) {
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
		else if (input->is_held(VK_LBUTTON)) {
			float fraction = (float)(input->mouse_x - (x + 5)) / w;
			fraction = std::clamp(fraction, 0.0f, 1.0f);

			float newval = (fraction * (max - min)) / (1 / step) * (1 / step) + min;
			if (newval != var) {
				var = newval;
				callback = true;
			}
			//draw.outlined_string( ESP, , { 255, 255, 255, 255 }, ALIGN_CENTERHORIZONTAL, "%.2f", var );
		}

		int textx = std::clamp(x + sliderx + 6, x + 15, x + w - 5);
		render->outlined_text(x + w + 5, y - 13, ALIGN_RIGHT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, format, var);

		render->filled_rect(x + sliderx + 4, y - 1, 3, 9, color(152, 50, 1));
		render->outlined_rect(x + sliderx + 3, y - 2, 5, 11, config->m_colors.m_ui_accent);
	}

	else {
		render->filled_rect(x + 5, y, w, h, config->m_colors.m_ui_background);
		render->filled_rect(x + sliderx + 5, y + 1, w - sliderx - 1, h - 2, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 7;

	return callback;
}

bool c_menu::key_bind(std::string label, unsigned short& var) {
	auto VK2STR = [&](const short key) -> std::string {
		switch (key) {
		case VK_LBUTTON: return ("Left Mouse");
		case VK_RBUTTON: return ("Right Mouse");
		case VK_MBUTTON: return ("Middle Mouse");
		case VK_XBUTTON1: return ("Mouse4");
		case VK_XBUTTON2: return ("Mouse5");
		case 0x0: return ("None");
		default: break;
		}

		CHAR output[16] = { "\0" };

		if (GetKeyNameTextA(MapVirtualKeyA(key, MAPVK_VK_TO_VSC) << 16, output, 16))
			return output;

		return ("None");
	};

	bool callback = false;

	int x = m_last_group.m_x;
	int y = m_last_group.m_y - 5;
	int w = 90;
	int h = 15;

	static float time = ctx->m_engine_client->time();
	float elapsed = ctx->m_engine_client->time() - time;

	static unsigned short* curr = nullptr, * prevv = curr;
	if (curr != prevv) {
		time = ctx->m_engine_client->time();
		prevv = curr;
	}

	if (curr == nullptr && elapsed > 0.1f && input->is_pressed(VK_LBUTTON) && !m_combobox_open && !m_multi_combobox_open) {
		if (input->in_area(x, y, w, h)) {
			curr = &var;
			press_sound();
			input->null_key(VK_LBUTTON);
		}
	}

	static float time_notactive = 0.0f;

	render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
	if ((input->in_area(x, y, w, h) || curr == &var) && !m_combobox_open && !m_multi_combobox_open)
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, { config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80 });

	else {
		render->filled_rect(x + 5, y, w, h, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	if (curr == &var && !m_combobox_open && !m_multi_combobox_open) {
		m_typing = true;

		if (ctx->m_engine_client->time() - time_notactive > 0.1f) {
			input->prevent_inputs = false;
			for (short n = 0; n < 256; n++) {
				if ((n > 0x0 && n < 0x7) || (n > 'A' - 1 && n < 'Z' + 1) || n == VK_LSHIFT || n == VK_RSHIFT || n == VK_SHIFT || n == VK_ESCAPE || n == VK_INSERT) {
					if (input->is_pressed(n)) {
						if (n == VK_INSERT) {
							curr = nullptr;
							break;
						}

						if (n == VK_ESCAPE) {
							var = 0x0;
							curr = nullptr;
							break;
						}

						var = n;
						curr = nullptr;
						callback = true;
						break;
					}
				}
			}
		}

		input->prevent_inputs = true;
		render->outlined_text(x + (w / 2) + 5, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, "Press a Key");
		//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTER, "Press a Key" );
	}

	else {
		input->prevent_inputs = true;
		if (curr == nullptr) {
			time_notactive = ctx->m_engine_client->time();
			input->prevent_inputs = false;
		}
		render->outlined_text(x + (w / 2) + 5, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, "%s", VK2STR(var).c_str());
		//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTER, "%s", VK2STR( var ).c_str( ) );
	}

	render->outlined_text(x + w + 10, y + (h / 2), ALIGN_CENTERVERTICAL, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTERVERTICAL, label.c_str( ) );

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 10;

	return callback;
}

bool c_menu::text_box(std::string label, std::string& var) {
	bool callback = false;

	int x = m_last_group.m_x;
	int y = m_last_group.m_y - 5;
	int w = 90;
	int h = 15;

	static float time = ctx->m_engine_client->time();
	float elapsed = ctx->m_engine_client->time() - time;

	static std::string* curr = nullptr, * prevv = curr;
	std::string preview;
	if (curr != prevv) {
		time = ctx->m_engine_client->time();
		prevv = curr;
	}

	if (curr == nullptr && elapsed > 0.1f && input->is_pressed(VK_LBUTTON) && !m_combobox_open && !m_multi_combobox_open) {
		if (input->in_area(x, y, w, h)) {
			curr = &var;
			input->null_key(VK_LBUTTON);
		}
	}

	static float time_notactive = 0.0f;

	render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
	if ((input->in_area(x, y, w, h) || curr == &var) && !m_combobox_open && !m_multi_combobox_open)
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, { config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80 });

	else {
		render->filled_rect(x + 5, y - 5, w, h, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y - 5, w, h, config->m_colors.m_ui_foreground);
	}

	if (curr == &var) {
		m_typing = true;
		input->prevent_inputs = false;

		if (input->is_pressed(VK_INSERT) || input->is_pressed(VK_ESCAPE)) {
			curr = nullptr;
			return false;
		}

		if (var.length() < 21) {
			if (input->is_pressed(VK_SPACE))
				var += char(VK_SPACE);

			for (int16_t key = 'A'; key < 'Z' + 1; key++) {
				if (input->is_pressed(key)) {
					if (input->is_held(VK_LSHIFT) || input->is_held(VK_RSHIFT) || (GetKeyState(VK_CAPITAL) & 0x1))
						var += char(key);

					else var += char(key + 32);
				}
			}
		}

		if (input->is_pressed_and_held(VK_BACK) && !var.empty())
			var.erase(var.end() - 1);

		if (input->is_pressed(VK_RETURN)) {
			curr = nullptr;
			callback = true;
		}

		preview = var;
		int text_w, text_h;
		ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(preview).c_str(), text_w, text_h);

		if (text_w > w - 5) {
			const int count = preview.length() - 7;
			preview.erase(preview.end() - (int)count, preview.end());
			preview.append("...");
		}

		input->prevent_inputs = true;
		render->outlined_text(x + (w / 2) + 5, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, { 255, 255, 255, 255 }, preview.empty() ? ("Enter text") : preview.c_str());
		//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTER, preview.empty( ) ? ( "Enter text" ) : preview.c_str( ) );
	}

	else {
		preview = var;

		int text_w, text_h;
		ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(preview).c_str(), text_w, text_h);

		if (text_w > w - 5) {
			const int count = preview.length() - 7;
			preview.erase(preview.end() - (int)count, preview.end());
			preview.append("...");
		}

		render->outlined_text(x + (w / 2) + 5, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, { 255, 255, 255, 255 }, preview.empty() ? ("Enter text") : preview.c_str());
		//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTER, preview.empty( ) ? ( "Enter text" ) : preview.c_str( ) );
	}

	render->outlined_text(x + w + 10, y + (h / 2), ALIGN_CENTERVERTICAL, ctx->m_tahoma_narrow.m_font, { 255, 255, 255, 255 }, label.c_str());
	//draw.outlined_string( ESP, , , { 255, 255, 255, 255 }, ALIGN_CENTERVERTICAL, label.c_str( ) );

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 10;

	return callback;
}

bool c_menu::combo_box(std::string label, int& var, std::vector< const char* > items) {
	bool callback = false;

	int x = m_last_group.m_x;
	int y = m_last_group.m_y - 5;
	int w = 90;
	int h = 15;

	int real_height = h + items.size() * 15 + 1;

	static float time = ctx->m_engine_client->time();
	float elapsed = ctx->m_engine_client->time() - time;

	static int* curr = nullptr, * prev = curr;
	std::string preview;
	if (curr != prev) {
		time = ctx->m_engine_client->time();
		prev = curr;
	}

	if (curr == &var && elapsed > 0.1f && input->is_pressed(VK_LBUTTON)) {
		if (!input->in_area(x, y, w, real_height)) {
			m_combobox_open = false;
			m_combo_info.m_var = nullptr;
			curr = nullptr;
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
	}

	if (curr == nullptr && elapsed > 0.1f && input->is_pressed(VK_LBUTTON) && !m_multi_combobox_open) {
		if (input->in_area(x, y, w, h)) {
			curr = &var;
			input->null_key(VK_LBUTTON);
			m_combo_info.m_area = { x, y, w, h };
			m_combo_info.m_items = items;
			press_sound();
		}
	}

	if (input->is_pressed(VK_INSERT) || input->is_pressed(VK_ESCAPE)) {
		m_combobox_open = false;
		m_combo_info.m_var = nullptr;
		curr = nullptr;
	}

	if (input->in_area(x, y, w, h) || curr == &var) {
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, { config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80 });
	}
	else {
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	preview = label;
	int wide, tall;
	ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(label.c_str()).c_str(), wide, tall);

	if (wide > w - 5) {
		const int count = preview.length() - 5;
		preview.erase(preview.end() - (int)count, preview.end());
		preview.append("...");
	}

	render->outlined_text(x + 5 + w / 2, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, preview.c_str());

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 10;

	m_combo_info.m_var = curr;
	//m_combo_info.m_var = prev;

	return callback;
}

bool c_menu::update_combo() {
	bool callback = false;
	int x = m_combo_info.m_area.m_x;
	int y = m_combo_info.m_area.m_y;
	int w = m_combo_info.m_area.m_w;
	int h = m_combo_info.m_area.m_h;
	int real_height = h + m_combo_info.m_items.size() * 15 + 1;

	if (m_combo_info.m_var && input->is_pressed(VK_LBUTTON)) {
		if (!input->in_area(x, y, w, real_height)) {
			m_combobox_open = false;
			m_combo_info.m_var = nullptr;
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
	}

	if (m_combo_info.m_var && !m_multi_combobox_open) {
		m_combobox_open = true;

		for (size_t i = 0; i < m_combo_info.m_items.size(); i++) {
			int addedheight = ((i + 1) * 15) + 1;
			const char* item = m_combo_info.m_items.at(i);

			if (input->in_area(x + 5, y + addedheight, w, h - 1)) {
				if (input->is_pressed(VK_LBUTTON)) {
					*m_combo_info.m_var = i;
					press_sound();
					callback = true;
				}
			}

			if (*m_combo_info.m_var == i)
			{
				render->filled_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_accent);
			}
			else if (input->in_area(x + 5, y + addedheight, w, h - 1))
			{
				render->filled_rect(x + 5, y + addedheight, w, h, color(116, 22, 22));
			}
			else
			{
				render->filled_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_background);
			}

			render->outlined_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_foreground);

			std::string preview = item;
			int wide, tall;
			ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(item).c_str(), wide, tall);

			if (wide > w - 5) {
				const int count = preview.length() - 5;
				preview.erase(preview.end() - (int)count, preview.end());
				preview.append("...");
			}
			render->outlined_text(x + 5 + w / 2, y + addedheight + h / 2, ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, preview.c_str());
		}
	}

	return callback;
}

bool c_menu::multi_combo_box(std::string label, std::vector< std::pair<const char*, bool*> > items) {
	bool callback = false;

	int x = m_last_group.m_x;
	int y = m_last_group.m_y - 5;
	int w = 90;
	int h = 15;

	int real_height = h + items.size() * 15 + 1;

	static float time = ctx->m_engine_client->time();
	float elapsed = ctx->m_engine_client->time() - time;

	static std::string* curr = nullptr, * prev = curr;
	std::string preview;
	if (curr != prev) {
		time = ctx->m_engine_client->time();
		prev = curr;
	}

	if (curr == &label && elapsed > 0.1f && input->is_pressed(VK_LBUTTON)) {
		if (!input->in_area(x, y, w, real_height)) {
			m_multi_combobox_open = false;
			m_multi_combo_info.m_label = nullptr;
			curr = nullptr;
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
	}

	if (curr == nullptr && elapsed > 0.1f && input->is_pressed(VK_LBUTTON) && !m_combobox_open) {
		if (input->in_area(x, y, w, h)) {
			curr = &label;
			input->null_key(VK_LBUTTON);
			m_multi_combo_info.m_area = { x, y, w, h };
			m_multi_combo_info.m_items = items;
			press_sound();
		}
	}

	if (input->is_pressed(VK_INSERT) || input->is_pressed(VK_ESCAPE)) {
		m_multi_combobox_open = false;
		m_multi_combo_info.m_label = nullptr;
		curr = nullptr;
	}

	if (input->in_area(x, y, w, h) || curr == &label) {
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_accent);
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, { config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 80 });
	}
	else {
		render->filled_rect(x + 6, y + 1, w - 2, h - 2, config->m_colors.m_ui_background);
		render->outlined_rect(x + 5, y, w, h, config->m_colors.m_ui_foreground);
	}

	preview = label;
	int wide, tall;
	ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(label.c_str()).c_str(), wide, tall);

	if (wide > w - 5) {
		const int count = preview.length() - 5;
		preview.erase(preview.end() - (int)count, preview.end());
		preview.append("...");
	}

	render->outlined_text(x + 5 + w / 2, y + (h / 2), ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, preview.c_str());

	m_last_group.m_x = x;
	m_last_group.m_y = y + h + 10;

	m_multi_combo_info.m_label = curr;

	return callback;
}

bool c_menu::update_multi_combo() {
	bool callback = false;
	int x = m_multi_combo_info.m_area.m_x;
	int y = m_multi_combo_info.m_area.m_y;
	int w = m_multi_combo_info.m_area.m_w;
	int h = m_multi_combo_info.m_area.m_h;
	int real_height = h + m_multi_combo_info.m_items.size() * 15 + 1;

	if (m_multi_combo_info.m_label && input->is_pressed(VK_LBUTTON)) {
		if (!input->in_area(x, y, w, real_height)) {
			m_multi_combobox_open = false;
			m_multi_combo_info.m_label = nullptr;
			ctx->m_surface->play_sound("ui/buttonclickrelease.wav");
		}
	}

	if (m_multi_combo_info.m_label && !m_combobox_open) {
		m_multi_combobox_open = true;

		for (size_t i = 0; i < m_multi_combo_info.m_items.size(); i++) {
			int addedheight = ((i + 1) * 15) + 1;
			const char* item = m_multi_combo_info.m_items.at(i).first;

			if (input->in_area(x + 5, y + addedheight, w, h - 1)) {
				if (input->is_pressed(VK_LBUTTON)) {
					*m_multi_combo_info.m_items.at(i).second = !*m_multi_combo_info.m_items.at(i).second;
					press_sound();
					callback = true;
				}
			}

			if (*m_multi_combo_info.m_items.at(i).second)
			{
				render->filled_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_accent);
			}
			else if (input->in_area(x + 5, y + addedheight, w, h - 1))
			{
				render->filled_rect(x + 5, y + addedheight, w, h, color(116, 22, 22));
			}
			else
			{
				render->filled_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_background);
			}

			render->outlined_rect(x + 5, y + addedheight, w, h, config->m_colors.m_ui_foreground);

			std::string preview = item;
			int wide, tall;
			ctx->m_surface->get_text_size(ctx->m_tahoma_narrow.m_font, util::utf_to_wide(item).c_str(), wide, tall);

			if (wide > w - 5) {
				const int count = preview.length() - 5;
				preview.erase(preview.end() - (int)count, preview.end());
				preview.append("...");
			}
			render->outlined_text(x + 5 + w / 2, y + addedheight + h / 2, ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, preview.c_str());
		}
	}

	return callback;
}

void c_menu::enable_clipping(rect_t size) {
	ctx->m_surface->get_clipping_rect(m_backup_left, m_backup_top, m_backup_right, m_backup_bottom, m_backup_clipping_disabled);

	ctx->m_surface->disable_clipping(false);
	ctx->m_surface->set_clipping_rect(size.m_x, size.m_y, size.m_x + size.m_w, size.m_y + size.m_h);
}

void c_menu::disable_clipping() {
	ctx->m_surface->disable_clipping(m_backup_clipping_disabled);
	ctx->m_surface->set_clipping_rect(m_backup_left, m_backup_top, m_backup_right, m_backup_bottom);
}

void c_menu::save_config() {
	std::ofstream output("figgy.jenga");

	if (output.is_open()) {
		Json::Value Save;

		Save["m_aimbot_global"]["m_enabled"] = config->m_aimbot_global.m_enabled;
		Save["m_aimbot_global"]["m_aim_key"] = config->m_aimbot_global.m_aim_key.m_key;
		Save["m_aimbot_global"]["m_ignore_friends"] = config->m_aimbot_global.m_ignore_friends;
		Save["m_aimbot_global"]["m_ignore_cloaked"] = config->m_aimbot_global.m_ignore_cloaked;
		Save["m_aimbot_global"]["m_aim_fov"] = config->m_aimbot_global.m_aim_fov;

		Save["m_aimbot"]["m_auto_scope"] = config->m_aimbot.m_auto_scope;
		Save["m_aimbot"]["m_aim_stickies"] = config->m_aimbot.m_aim_stickies;
		Save["m_aimbot"]["m_baim_on_lethal"] = config->m_aimbot.m_baim_on_lethal;
		Save["m_aimbot"]["m_delayshot"] = config->m_aimbot.m_delayshot;
		Save["m_aimbot"]["m_delayshot_precent"] = config->m_aimbot.m_delayshot_percent;
		Save["m_aimbot"]["m_enabled"] = config->m_aimbot.m_enabled;
		Save["m_aimbot"]["m_heavy_mp"] = config->m_aimbot.m_heavy_mp;
		Save["m_aimbot"]["m_sniper_mp"] = config->m_aimbot.m_sniper_mp;
		Save["m_aimbot"]["m_require_key"] = config->m_aimbot.m_require_key;
		Save["m_aimbot"]["m_scout_mp"] = config->m_aimbot.m_scout_mp;
		Save["m_aimbot"]["m_tap_fire"] = config->m_aimbot.m_tap_fire;
		Save["m_aimbot"]["m_tap_fire_distance"] = config->m_aimbot.m_tap_fire_distance;
		Save["m_aimbot"]["m_safe_point"] = config->m_aimbot.m_safe_point;

		Save["m_automations"]["m_auto_detonate"] = config->m_automations.m_auto_detonate;
		Save["m_automations"]["m_enabled"] = config->m_automations.m_enabled;
		Save["m_automations"]["m_auto_detonate_distance"] = config->m_automations.m_auto_detonate_distance;
		Save["m_automations"]["m_charge_max"] = config->m_automations.m_charge_max;
		Save["m_automations"]["m_auto_vaccinator"] = config->m_automations.m_auto_vaccinator;
		Save["m_automations"]["m_auto_vaccinator_player_threat"] = config->m_automations.m_auto_vaccinator_player_threat;
		Save["m_automations"]["m_auto_vaccinator_projectile_prediction"] = config->m_automations.m_auto_vaccinator_projectile_prediction;
		Save["m_automations"]["m_auto_vaccinator_projectile_threat"] = config->m_automations.m_auto_vaccinator_projectile_threat;
		Save["m_automations"]["m_auto_vacc_pop"] = config->m_automations.m_auto_vacc_pop;
		Save["m_automations"]["m_auto_vac_switch_delay"] = config->m_automations.m_auto_vac_switch_delay;

		Save["m_esp"]["m_building_box"] = config->m_esp.m_building_box;
		Save["m_esp"]["m_building_enemy"] = config->m_esp.m_building_enemy;
		Save["m_esp"]["m_building_flags"] = config->m_esp.m_building_flags;
		Save["m_esp"]["m_building_health"] = config->m_esp.m_building_health;
		Save["m_esp"]["m_building_name"] = config->m_esp.m_building_name;
		Save["m_esp"]["m_players_enabled"] = config->m_esp.m_players_enabled;
		Save["m_esp"]["m_buildings_enabled"] = config->m_esp.m_buildings_enabled;
		Save["m_esp"]["m_player_box"] = config->m_esp.m_player_box;
		Save["m_esp"]["m_player_enemy"] = config->m_esp.m_player_enemy;
		Save["m_esp"]["m_player_flags"] = config->m_esp.m_player_flags;
		Save["m_esp"]["m_player_health"] = config->m_esp.m_player_health;
		Save["m_esp"]["m_player_name"] = config->m_esp.m_player_name;
		Save["m_esp"]["m_player_team_color"] = config->m_esp.m_player_team_color;
		Save["m_esp"]["m_player_weapon"] = config->m_esp.m_player_weapon;
		Save["m_esp"]["m_projectile_box"] = config->m_esp.m_projectile_box;
		Save["m_esp"]["m_projectile_distance"] = config->m_esp.m_projectile_distance;
		Save["m_esp"]["m_projectile_enemy"] = config->m_esp.m_projectile_enemy;
		Save["m_esp"]["m_projectile_flags"] = config->m_esp.m_projectile_flags;
		Save["m_esp"]["m_projectile_name"] = config->m_esp.m_projectile_name;
		Save["m_esp"]["m_world_enabled"] = config->m_esp.m_world_enabled;
		Save["m_esp"]["m_world_name"] = config->m_esp.m_world_name;
		Save["m_esp"]["m_world_box"] = config->m_esp.m_world_box;
		Save["m_esp"]["m_world_distance"] = config->m_esp.m_world_distance;
		Save["m_esp"]["m_far_esp_fade_t"] = config->m_esp.m_far_esp_fade_t;
		Save["m_esp"]["m_predict_stickies"] = config->m_esp.m_predict_stickies;
		Save["m_esp"]["m_player_arrows"] = config->m_esp.m_player_arrows;
		Save["m_esp"]["m_arrows_screen_distance"] = config->m_esp.m_arrows_screen_distance;
		Save["m_esp"]["m_arrows_screen_shape"] = config->m_esp.m_arrows_screen_shape;
		Save["m_esp"]["m_arrows_esp"] = config->m_esp.m_arrows_esp;

		Save["m_models"]["m_enabled"] = config->m_models.m_enabled;
		Save["m_models"]["m_rendering_order"] = config->m_models.m_rendering_order;
		Save["m_models"]["m_player_models"] = config->m_models.m_player_models;
		Save["m_models"]["m_player_enemy_only"] = config->m_models.m_player_enemy_only;
		Save["m_models"]["m_player_ignorez"] = config->m_models.m_player_ignorez;
		Save["m_models"]["m_player_overlay"] = config->m_models.m_player_overlay;
		Save["m_models"]["m_player_overlay_occluded"] = config->m_models.m_player_overlay_occluded;
		Save["m_models"]["m_player_overlay_unoccluded"] = config->m_models.m_player_overlay_unoccluded;
		Save["m_models"]["m_player_two_models"] = config->m_models.m_player_two_models;
		Save["m_models"]["m_player_alpha_unoccluded"] = config->m_models.m_player_alpha_unoccluded;
		Save["m_models"]["m_player_alpha_occluded"] = config->m_models.m_player_alpha_occluded;
		Save["m_models"]["m_player_alpha"] = config->m_models.m_player_alpha;
		Save["m_models"]["m_player_model"] = config->m_models.m_player_model;
		Save["m_models"]["m_player_model_occluded"] = config->m_models.m_player_model_occluded;
		Save["m_models"]["m_player_model_unoccluded"] = config->m_models.m_player_model_unoccluded;
		Save["m_models"]["m_player_attachments"] = config->m_models.m_player_attachments;
		Save["m_models"]["m_backtrack_models"] = config->m_models.m_backtrack_models;
		Save["m_models"]["m_backtrack_last_only"] = config->m_models.m_backtrack_last_only;

		Save["m_models"]["m_building_models"] = config->m_models.m_building_models;
		Save["m_models"]["m_building_enemy_only"] = config->m_models.m_building_enemy_only;
		Save["m_models"]["m_building_ignorez"] = config->m_models.m_building_ignorez;
		Save["m_models"]["m_building_overlay"] = config->m_models.m_building_overlay;
		Save["m_models"]["m_building_overlay_occluded"] = config->m_models.m_building_overlay_occluded;
		Save["m_models"]["m_building_overlay_unoccluded"] = config->m_models.m_building_overlay_unoccluded;
		Save["m_models"]["m_building_two_models"] = config->m_models.m_building_two_models;
		Save["m_models"]["m_building_alpha_unoccluded"] = config->m_models.m_building_alpha_unoccluded;
		Save["m_models"]["m_building_alpha_occluded"] = config->m_models.m_building_alpha_occluded;
		Save["m_models"]["m_building_alpha"] = config->m_models.m_building_alpha;
		Save["m_models"]["m_building_model"] = config->m_models.m_building_model;
		Save["m_models"]["m_building_model_occluded"] = config->m_models.m_building_model_occluded;
		Save["m_models"]["m_building_model_unoccluded"] = config->m_models.m_building_model_unoccluded;

		Save["m_models"]["m_world_models"] = config->m_models.m_world_models;
		Save["m_models"]["m_world_ignorez"] = config->m_models.m_world_ignorez;
		Save["m_models"]["m_world_overlay"] = config->m_models.m_world_overlay;
		Save["m_models"]["m_world_overlay_occluded"] = config->m_models.m_world_overlay_occluded;
		Save["m_models"]["m_world_overlay_unoccluded"] = config->m_models.m_world_overlay_unoccluded;
		Save["m_models"]["m_world_two_models"] = config->m_models.m_world_two_models;
		Save["m_models"]["m_world_alpha_unoccluded"] = config->m_models.m_world_alpha_unoccluded;
		Save["m_models"]["m_world_alpha_occluded"] = config->m_models.m_world_alpha_occluded;
		Save["m_models"]["m_world_alpha"] = config->m_models.m_world_alpha;
		Save["m_models"]["m_world_model"] = config->m_models.m_world_model;
		Save["m_models"]["m_world_model_occluded"] = config->m_models.m_world_model_occluded;
		Save["m_models"]["m_world_model_unoccluded"] = config->m_models.m_world_model_unoccluded;

		Save["m_models"]["m_projectile_models"] = config->m_models.m_projectile_models;
		Save["m_models"]["m_projectile_enemy_only"] = config->m_models.m_projectile_enemy_only;
		Save["m_models"]["m_projectile_ignorez"] = config->m_models.m_projectile_ignorez;
		Save["m_models"]["m_projectile_overlay"] = config->m_models.m_projectile_overlay;
		Save["m_models"]["m_projectile_overlay_occluded"] = config->m_models.m_projectile_overlay_occluded;
		Save["m_models"]["m_projectile_overlay_unoccluded"] = config->m_models.m_projectile_overlay_unoccluded;
		Save["m_models"]["m_projectile_two_models"] = config->m_models.m_projectile_two_models;
		Save["m_models"]["m_projectile_alpha_unoccluded"] = config->m_models.m_projectile_alpha_unoccluded;
		Save["m_models"]["m_projectile_alpha_occluded"] = config->m_models.m_projectile_alpha_occluded;
		Save["m_models"]["m_projectile_alpha"] = config->m_models.m_projectile_alpha;
		Save["m_models"]["m_projectile_model"] = config->m_models.m_projectile_model;
		Save["m_models"]["m_projectile_model_occluded"] = config->m_models.m_projectile_model_occluded;
		Save["m_models"]["m_projectile_model_unoccluded"] = config->m_models.m_projectile_model_unoccluded;

		Save["m_outlines"]["m_enabled"] = config->m_outlines.m_enabled;
		Save["m_outlines"]["m_blur_outline"] = config->m_outlines.m_blur_outline;
		Save["m_outlines"]["m_blur_scale"] = config->m_outlines.m_blur_scale;
		Save["m_outlines"]["m_stencil_outline"] = config->m_outlines.m_stencil_outline;
		Save["m_outlines"]["m_stencil_scale"] = config->m_outlines.m_stencil_scale;

		Save["m_outlines"]["m_player_outlines"] = config->m_outlines.m_player_outlines;
		Save["m_outlines"]["m_player_enemy_only"] = config->m_outlines.m_player_enemy_only;
		Save["m_outlines"]["m_player_alpha"] = config->m_outlines.m_player_alpha;

		Save["m_outlines"]["m_building_outlines"] = config->m_outlines.m_building_outlines;
		Save["m_outlines"]["m_building_enemy_only"] = config->m_outlines.m_building_enemy_only;
		Save["m_outlines"]["m_building_alpha"] = config->m_outlines.m_building_alpha;

		Save["m_outlines"]["m_projectile_outlines"] = config->m_outlines.m_projectile_outlines;
		Save["m_outlines"]["m_projectile_enemy_only"] = config->m_outlines.m_projectile_enemy_only;
		Save["m_outlines"]["m_projectile_alpha"] = config->m_outlines.m_projectile_alpha;

		Save["m_outlines"]["m_world_outlines"] = config->m_outlines.m_world_outlines;
		Save["m_outlines"]["m_world_alpha"] = config->m_outlines.m_world_alpha;

		Save["m_exploits"]["m_crithack"] = config->m_exploits.m_crithack;
		Save["m_exploits"]["m_crithack_indicator"] = config->m_exploits.m_crithack_indicator;
		Save["m_exploits"]["m_crithack_key"] = config->m_exploits.m_crithack_key.m_key;
		Save["m_exploits"]["m_doubletap"] = config->m_exploits.m_doubletap;
		Save["m_exploits"]["m_doubletap_indicator"] = config->m_exploits.m_doubletap_indicator;
		Save["m_exploits"]["m_doubletap_in_air"] = config->m_exploits.m_doubletap_in_air;
		Save["m_exploits"]["m_doubletap_recharge_key"] = config->m_exploits.m_doubletap_recharge_key.m_key;
		Save["m_exploits"]["m_dynamic_warp_ticks"] = config->m_exploits.m_dynamic_warp_ticks;
		Save["m_exploits"]["m_no_choke"] = config->m_exploits.m_no_choke;
		Save["m_exploits"]["m_tickbase_warp_key"] = config->m_exploits.m_tickbase_warp_key.m_key;
		Save["m_exploits"]["m_warp"] = config->m_exploits.m_warp;
		Save["m_exploits"]["m_warp_speed"] = config->m_exploits.m_warp_speed;
		Save["m_exploits"]["m_auto_warp"] = config->m_exploits.m_auto_warp;
		Save["m_exploits"]["m_auto_warp_key"] = config->m_exploits.m_auto_warp_key.m_key;
		Save["m_exploits"]["m_auto_warp_scale"] = config->m_exploits.m_auto_warp_scale;
		Save["m_exploits"]["m_fake_latency_amount"] = config->m_exploits.m_fake_latency_amount;
		Save["m_exploits"]["m_fake_latency"] = config->m_exploits.m_fake_latency;
		Save["m_exploits"]["m_backtrack"] = config->m_exploits.m_backtrack;

		Save["m_misc"]["m_auto_strafer"] = config->m_misc.m_auto_strafer;
		Save["m_misc"]["m_avoid_push"] = config->m_misc.m_avoid_push;
		Save["m_misc"]["m_bunnyhop"] = config->m_misc.m_bunnyhop;
		Save["m_misc"]["m_fast_stop"] = config->m_misc.m_fast_stop;
		Save["m_misc"]["m_scout_jump"] = config->m_misc.m_scout_jump;
		Save["m_misc"]["m_scout_jump_key"] = config->m_misc.m_scout_jump_key.m_key;
		Save["m_misc"]["m_taunt_slide"] = config->m_misc.m_taunt_slide;
		Save["m_misc"]["m_skip_welcome"] = config->m_misc.m_skip_welcome;
		Save["m_misc"]["m_vote_revealer"] = config->m_misc.m_vote_revealer;
		Save["m_misc"]["m_reduce_input_delay"] = config->m_misc.m_reduce_input_delay;
		Save["m_misc"]["m_chat_player_connects"] = config->m_misc.m_chat_player_connects;
		Save["m_misc"]["m_chat_player_disconnects"] = config->m_misc.m_chat_player_disconnects;
		Save["m_misc"]["m_chat_player_class_changes"] = config->m_misc.m_chat_player_class_changes;
		Save["m_misc"]["m_chat_player_name_changes"] = config->m_misc.m_chat_player_name_changes;
		Save["m_misc"]["m_chat_vote_casts"] = config->m_misc.m_chat_vote_casts;

		Save["m_projectile_aim"]["m_auto_shoot"] = config->m_projectile_aim.m_auto_shoot;
		Save["m_projectile_aim"]["m_draw_prediction_path"] = config->m_projectile_aim.m_draw_prediction_path;
		Save["m_projectile_aim"]["m_draw_projectile_path"] = config->m_projectile_aim.m_draw_projectile_path;
		Save["m_projectile_aim"]["m_projectile_path_any_angle"] = config->m_projectile_aim.m_projectile_path_any_angle;
		Save["m_projectile_aim"]["m_enabled"] = config->m_projectile_aim.m_enabled;
		Save["m_projectile_aim"]["m_hitchance"] = config->m_projectile_aim.m_hitchance;
		Save["m_projectile_aim"]["m_max_simulation_time"] = config->m_projectile_aim.m_max_simulation_time;
		Save["m_projectile_aim"]["m_sample_time"] = config->m_projectile_aim.m_sample_time;
		Save["m_projectile_aim"]["m_optimized_prediction"] = config->m_projectile_aim.m_optimized_prediction;
		Save["m_projectile_aim"]["m_turn_prediction"] = config->m_projectile_aim.m_turn_prediction;
		Save["m_projectile_aim"]["m_target_sorting"] = config->m_projectile_aim.m_target_sorting;

		Save["m_melee_aim"]["m_enable"] = config->m_melee_aim.m_enable;
		Save["m_melee_aim"]["m_if_backstable"] = config->m_melee_aim.m_if_backstable;
		Save["m_melee_aim"]["m_require_aimkey"] = config->m_melee_aim.m_require_aimkey;
		Save["m_melee_aim"]["m_smack_friends"] = config->m_melee_aim.m_smack_friends;
		Save["m_melee_aim"]["m_smack_friedly_buildings"] = config->m_melee_aim.m_smack_friedly_buildings;

		Save["m_visuals"]["m_remove_recoil"] = config->m_visuals.m_remove_recoil;
		Save["m_visuals"]["m_bullet_tracers"] = config->m_visuals.m_bullet_tracers;
		Save["m_visuals"]["m_field_of_view"] = config->m_visuals.m_field_of_view;
		Save["m_visuals"]["m_mvm_giant_sounds"] = config->m_visuals.m_mvm_giant_sounds;
		Save["m_visuals"]["m_sniper_sightlines"] = config->m_visuals.m_sniper_sightlines;
		Save["m_visuals"]["m_thirdperson"] = config->m_visuals.m_thirdperson;
		Save["m_visuals"]["m_thirdperson_key"] = config->m_visuals.m_thirdperson_key.m_key;
		Save["m_visuals"]["m_viewmodel_roll"] = config->m_visuals.m_viewmodel_roll;
		Save["m_visuals"]["m_viewmodel_sway"] = config->m_visuals.m_viewmodel_sway;
		Save["m_visuals"]["m_viewmodel_sway_val"] = config->m_visuals.m_viewmodel_sway_val;
		Save["m_visuals"]["m_viewmodel_x"] = config->m_visuals.m_viewmodel_x;
		Save["m_visuals"]["m_viewmodel_y"] = config->m_visuals.m_viewmodel_y;
		Save["m_visuals"]["m_viewmodel_z"] = config->m_visuals.m_viewmodel_z;
		Save["m_visuals"]["m_viewmodel_fov"] = config->m_visuals.m_viewmodel_fov;
		Save["m_visuals"]["m_remove_scope"] = config->m_visuals.m_remove_scope;
		Save["m_visuals"]["m_remove_zoom"] = config->m_visuals.m_remove_zoom;
		Save["m_visuals"]["m_visualize_aimbot"] = config->m_visuals.m_visualize_aimbot;
		Save["m_visuals"]["m_aspect_ratio"] = config->m_visuals.m_aspect_ratio;
		Save["m_visuals"]["m_zoomed_field_of_view"] = config->m_visuals.m_zoomed_field_of_view;
		Save["m_visuals"]["m_ragdolls_enabled"] = config->m_visuals.m_ragdolls_enabled;
		Save["m_visuals"]["m_ragdolls_enemy_only"] = config->m_visuals.m_ragdolls_enemy_only;
		Save["m_visuals"]["m_ragdoll_type"] = config->m_visuals.m_ragdoll_type;
		Save["m_visuals"]["m_ragdoll_burning"] = config->m_visuals.m_ragdoll_burning;
		Save["m_visuals"]["m_ragdoll_electrocuted"] = config->m_visuals.m_ragdoll_electrocuted;
		Save["m_visuals"]["m_ragdoll_dissolving"] = config->m_visuals.m_ragdoll_dissolving;
		Save["m_visuals"]["m_ragdoll_become_ash"] = config->m_visuals.m_ragdoll_become_ash;
		Save["m_visuals"]["m_prop_alpha"] = config->m_visuals.m_prop_alpha;

		Save["m_visuals"]["m_projectile_camera"] = config->m_visuals.m_projectile_camera;
		Save["m_visuals"]["m_projectile_camera_forward"] = config->m_visuals.m_projectile_camera_forward;
		Save["m_visuals"]["m_projectile_camera_right"] = config->m_visuals.m_projectile_camera_right;
		Save["m_visuals"]["m_projectile_camera_up"] = config->m_visuals.m_projectile_camera_up;
		Save["m_visuals"]["m_projectile_camera_fov"] = config->m_visuals.m_projectile_camera_fov;

		Save["m_visuals"]["camera_position.m_x"] = visuals->camera_position.m_x;
		Save["m_visuals"]["camera_position.m_y"] = visuals->camera_position.m_y;
		Save["m_visuals"]["camera_position.m_w"] = visuals->camera_position.m_w;
		Save["m_visuals"]["camera_position.m_h"] = visuals->camera_position.m_h;

		Save["m_hvh"]["m_fakelag"] = config->m_hvh.m_fakelag;
		Save["m_hvh"]["m_break_lag_comp"] = config->m_hvh.m_break_lag_comp;
		Save["m_hvh"]["m_max_ticks"] = config->m_hvh.m_max_ticks;
		Save["m_hvh"]["m_max_unchoke_del"] = config->m_hvh.m_max_unchoke_del;
		Save["m_hvh"]["m_fake_yaw.m_enabled"] = config->m_hvh.m_fake_yaw.m_enabled;
		Save["m_hvh"]["m_fake_yaw.m_anti_logic"] = config->m_hvh.m_fake_yaw.m_anti_logic;
		Save["m_hvh"]["m_fake_yaw.m_jitter"] = config->m_hvh.m_fake_yaw.m_jitter;
		Save["m_hvh"]["m_fake_yaw.m_jitter_max"] = config->m_hvh.m_fake_yaw.m_jitter_max;
		Save["m_hvh"]["m_fake_yaw.m_max_angle"] = config->m_hvh.m_fake_yaw.m_max_angle;
		Save["m_hvh"]["m_fake_yaw.m_min_angle"] = config->m_hvh.m_fake_yaw.m_min_angle;
		Save["m_hvh"]["m_real_yaw.m_enabled"] = config->m_hvh.m_real_yaw.m_enabled;
		Save["m_hvh"]["m_real_yaw.m_anti_logic"] = config->m_hvh.m_real_yaw.m_anti_logic;
		Save["m_hvh"]["m_real_yaw.m_edge"] = config->m_hvh.m_real_yaw.m_edge;
		Save["m_hvh"]["m_pitch.m_enabled"] = config->m_hvh.m_pitch.m_enabled;
		Save["m_hvh"]["m_pitch.m_jitter"] = config->m_hvh.m_pitch.m_jitter;
		Save["m_hvh"]["m_pitch.m_jitter_max"] = config->m_hvh.m_pitch.m_jitter_max;
		Save["m_hvh"]["m_pitch.m_max_angle"] = config->m_hvh.m_pitch.m_max_angle;
		Save["m_hvh"]["m_pitch.m_min_angle"] = config->m_hvh.m_pitch.m_min_angle;

		Save["m_menu"]["m_skull_background"] = config->m_menu.m_skull_background;

		output << Save;
		output.close();
	}
}

void c_menu::dump_server_players()
{
	std::ofstream output("players.txt", std::ios_base::app); // app allows to push to file

	// just for me g, i want to attempt doing smth
	for (const auto& player : ctx->players)
	{
		player_info_s info;
		ctx->m_engine_client->get_player_info(player->entindex(), &info);
		if (info.m_friends_id <= 0)
			continue;

		output << std::to_string(info.m_friends_id).c_str() << " : " << info.m_name << std::endl;
	}
	output.close();
}

void c_menu::load_config() {
	std::ifstream load("figgy.jenga");

	if (load.is_open()) {
		Json::Value Load;
		load >> Load;

		config->m_aimbot_global.m_enabled = Load["m_aimbot_global"]["m_enabled"].asBool();
		config->m_aimbot_global.m_aim_key.m_key = Load["m_aimbot_global"]["m_aim_key"].asInt();
		config->m_aimbot_global.m_ignore_friends = Load["m_aimbot_global"]["m_ignore_friends"].asBool();
		config->m_aimbot_global.m_ignore_cloaked = Load["m_aimbot_global"]["m_ignore_cloaked"].asBool();
		config->m_aimbot_global.m_aim_fov = Load["m_aimbot_global"]["m_aim_fov"].asInt();

		config->m_aimbot.m_auto_scope = Load["m_aimbot"]["m_auto_scope"].asBool();
		config->m_aimbot.m_aim_stickies = Load["m_aimbot"]["m_aim_stickies"].asBool();
		config->m_aimbot.m_baim_on_lethal = Load["m_aimbot"]["m_baim_on_lethal"].asBool();
		config->m_aimbot.m_delayshot = Load["m_aimbot"]["m_delayshot"].asBool();
		config->m_aimbot.m_delayshot_percent = Load["m_aimbot"]["m_delayshot_precent"].asInt();
		config->m_aimbot.m_enabled = Load["m_aimbot"]["m_enabled"].asBool();
		config->m_aimbot.m_heavy_mp = Load["m_aimbot"]["m_heavy_mp"].asFloat();
		config->m_aimbot.m_require_key = Load["m_aimbot"]["m_require_key"].asBool();
		config->m_aimbot.m_scout_mp = Load["m_aimbot"]["m_scout_mp"].asFloat();
		config->m_aimbot.m_sniper_mp = Load["m_aimbot"]["m_sniper_mp"].asFloat();
		config->m_aimbot.m_tap_fire = Load["m_aimbot"]["m_tap_fire"].asBool();
		config->m_aimbot.m_safe_point = Load["m_aimbot"]["m_safe_point"].asBool();
		config->m_aimbot.m_tap_fire_distance = Load["m_aimbot"]["m_tap_fire_distance"].asInt();

		config->m_automations.m_auto_detonate = Load["m_automations"]["m_auto_detonate"].asBool();
		config->m_automations.m_enabled = Load["m_automations"]["m_enabled"].asBool();
		config->m_automations.m_auto_vacc_pop = Load["m_automations"]["m_auto_vacc_pop"].asBool();
		config->m_automations.m_auto_detonate_distance = Load["m_automations"]["m_auto_detonate_distance"].asFloat();
		config->m_automations.m_charge_max = Load["m_automations"]["m_charge_max"].asFloat();
		config->m_automations.m_auto_vaccinator = Load["m_automations"]["m_auto_vaccinator"].asBool();
		config->m_automations.m_auto_vaccinator_player_threat = Load["m_automations"]["m_auto_vaccinator_player_threat"].asInt();
		config->m_automations.m_auto_vaccinator_projectile_prediction = Load["m_automations"]["m_auto_vaccinator_projectile_prediction"].asInt();
		config->m_automations.m_auto_vaccinator_projectile_threat = Load["m_automations"]["m_auto_vaccinator_projectile_threat"].asInt();
		config->m_automations.m_auto_vac_switch_delay = Load["m_automations"]["m_auto_vac_switch_delay"].asInt();

		config->m_esp.m_building_box = Load["m_esp"]["m_building_box"].asBool();
		config->m_esp.m_building_enemy = Load["m_esp"]["m_building_enemy"].asBool();
		config->m_esp.m_building_flags = Load["m_esp"]["m_building_flags"].asBool();
		config->m_esp.m_building_health = Load["m_esp"]["m_building_health"].asBool();
		config->m_esp.m_building_name = Load["m_esp"]["m_building_name"].asBool();
		config->m_esp.m_players_enabled = Load["m_esp"]["m_players_enabled"].asBool();
		config->m_esp.m_buildings_enabled = Load["m_esp"]["m_buildings_enabled"].asBool();
		config->m_esp.m_player_box = Load["m_esp"]["m_player_box"].asBool();
		config->m_esp.m_player_enemy = Load["m_esp"]["m_player_enemy"].asBool();
		config->m_esp.m_player_flags = Load["m_esp"]["m_player_flags"].asBool();
		config->m_esp.m_player_health = Load["m_esp"]["m_player_health"].asBool();
		config->m_esp.m_player_name = Load["m_esp"]["m_player_name"].asBool();
		config->m_esp.m_player_team_color = Load["m_esp"]["m_player_team_color"].asBool();
		config->m_esp.m_player_weapon = Load["m_esp"]["m_player_weapon"].asBool();
		config->m_esp.m_projectile_box = Load["m_esp"]["m_projectile_box"].asBool();
		config->m_esp.m_projectile_distance = Load["m_esp"]["m_projectile_distance"].asBool();
		config->m_esp.m_projectile_enemy = Load["m_esp"]["m_projectile_enemy"].asBool();
		config->m_esp.m_projectile_flags = Load["m_esp"]["m_projectile_flags"].asBool();
		config->m_esp.m_projectile_name = Load["m_esp"]["m_projectile_name"].asBool();
		config->m_esp.m_world_enabled = Load["m_esp"]["m_world_enabled"].asBool();
		config->m_esp.m_world_name = Load["m_esp"]["m_world_name"].asBool();
		config->m_esp.m_world_box = Load["m_esp"]["m_world_box"].asBool();
		config->m_esp.m_world_distance = Load["m_esp"]["m_world_distance"].asBool();
		config->m_esp.m_predict_stickies = Load["m_esp"]["m_predict_stickies"].asBool();
		config->m_esp.m_far_esp_fade_t = Load["m_esp"]["m_far_esp_fade_t"].asInt();
		config->m_esp.m_player_arrows = Load["m_esp"]["m_player_arrows"].asBool();
		config->m_esp.m_arrows_screen_distance = Load["m_esp"]["m_arrows_screen_distance"].asFloat();
		config->m_esp.m_arrows_screen_shape = Load["m_esp"]["m_arrows_screen_shape"].asInt();
		config->m_esp.m_arrows_esp = Load["m_esp"]["m_arrows_esp"].asBool();

		config->m_models.m_enabled = Load["m_models"]["m_enabled"].asBool();
		config->m_models.m_rendering_order = Load["m_models"]["m_rendering_order"].asInt();
		config->m_models.m_player_models = Load["m_models"]["m_player_models"].asBool();
		config->m_models.m_player_enemy_only = Load["m_models"]["m_player_enemy_only"].asBool();
		config->m_models.m_player_ignorez = Load["m_models"]["m_player_ignorez"].asBool();
		config->m_models.m_player_two_models = Load["m_models"]["m_player_two_models"].asBool();
		config->m_models.m_player_alpha_unoccluded = Load["m_models"]["m_player_alpha_unoccluded"].asFloat();
		config->m_models.m_player_alpha_occluded = Load["m_models"]["m_player_alpha_occluded"].asFloat();
		config->m_models.m_player_alpha = Load["m_models"]["m_player_alpha"].asFloat();
		config->m_models.m_player_model = Load["m_models"]["m_player_model"].asInt();
		config->m_models.m_player_model_occluded = Load["m_models"]["m_player_model_occluded"].asInt();
		config->m_models.m_player_model_unoccluded = Load["m_models"]["m_player_model_unoccluded"].asInt();
		config->m_models.m_player_attachments = Load["m_models"]["m_player_attachments"].asBool();
		config->m_models.m_backtrack_models = Load["m_models"]["m_backtrack_models"].asBool();
		config->m_models.m_backtrack_last_only = Load["m_models"]["m_backtrack_last_only"].asBool();

		config->m_models.m_building_models = Load["m_models"]["m_building_models"].asBool();
		config->m_models.m_building_enemy_only = Load["m_models"]["m_building_enemy_only"].asBool();
		config->m_models.m_building_ignorez = Load["m_models"]["m_building_ignorez"].asBool();
		config->m_models.m_building_two_models = Load["m_models"]["m_building_two_models"].asBool();
		config->m_models.m_building_alpha_unoccluded = Load["m_models"]["m_building_alpha_unoccluded"].asFloat();
		config->m_models.m_building_alpha_occluded = Load["m_models"]["m_building_alpha_occluded"].asFloat();
		config->m_models.m_building_alpha = Load["m_models"]["m_building_alpha"].asFloat();
		config->m_models.m_building_model = Load["m_models"]["m_building_model"].asInt();
		config->m_models.m_building_model_occluded = Load["m_models"]["m_building_model_occluded"].asInt();
		config->m_models.m_building_model_unoccluded = Load["m_models"]["m_building_model_unoccluded"].asInt();

		config->m_models.m_world_models = Load["m_models"]["m_world_models"].asBool();
		config->m_models.m_world_ignorez = Load["m_models"]["m_world_ignorez"].asBool();
		config->m_models.m_world_two_models = Load["m_models"]["m_world_two_models"].asBool();
		config->m_models.m_world_alpha_unoccluded = Load["m_models"]["m_world_alpha_unoccluded"].asFloat();
		config->m_models.m_world_alpha_occluded = Load["m_models"]["m_world_alpha_occluded"].asFloat();
		config->m_models.m_world_alpha = Load["m_models"]["m_world_alpha"].asFloat();
		config->m_models.m_world_model = Load["m_models"]["m_world_model"].asInt();
		config->m_models.m_world_model_occluded = Load["m_models"]["m_world_model_occluded"].asInt();
		config->m_models.m_world_model_unoccluded = Load["m_models"]["m_world_model_unoccluded"].asInt();

		config->m_models.m_projectile_models = Load["m_models"]["m_projectile_models"].asBool();
		config->m_models.m_projectile_enemy_only = Load["m_models"]["m_projectile_enemy_only"].asBool();
		config->m_models.m_projectile_ignorez = Load["m_models"]["m_projectile_ignorez"].asBool();
		config->m_models.m_projectile_two_models = Load["m_models"]["m_projectile_two_models"].asBool();
		config->m_models.m_projectile_alpha_unoccluded = Load["m_models"]["m_projectile_alpha_unoccluded"].asFloat();
		config->m_models.m_projectile_alpha_occluded = Load["m_models"]["m_projectile_alpha_occluded"].asFloat();
		config->m_models.m_projectile_alpha = Load["m_models"]["m_projectile_alpha"].asFloat();
		config->m_models.m_projectile_model = Load["m_models"]["m_projectile_model"].asInt();
		config->m_models.m_projectile_model_occluded = Load["m_models"]["m_projectile_model_occluded"].asInt();
		config->m_models.m_projectile_model_unoccluded = Load["m_models"]["m_projectile_model_unoccluded"].asInt();

		config->m_outlines.m_enabled = Load["m_outlines"]["m_enabled"].asBool();
		config->m_outlines.m_blur_outline = Load["m_outlines"]["m_blur_outline"].asBool();
		config->m_outlines.m_blur_scale = Load["m_outlines"]["m_blur_scale"].asFloat();
		config->m_outlines.m_stencil_outline = Load["m_outlines"]["m_stencil_outline"].asBool();
		config->m_outlines.m_stencil_scale = Load["m_outlines"]["m_stencil_scale"].asFloat();

		config->m_outlines.m_player_outlines = Load["m_outlines"]["m_player_outlines"].asBool();
		config->m_outlines.m_player_enemy_only = Load["m_outlines"]["m_player_enemy_only"].asBool();
		config->m_outlines.m_player_alpha = Load["m_outlines"]["m_player_alpha"].asFloat();

		config->m_outlines.m_building_outlines = Load["m_outlines"]["m_building_outlines"].asBool();
		config->m_outlines.m_building_enemy_only = Load["m_outlines"]["m_building_enemy_only"].asBool();
		config->m_outlines.m_building_alpha = Load["m_outlines"]["m_building_alpha"].asFloat();

		config->m_outlines.m_projectile_outlines = Load["m_outlines"]["m_projectile_outlines"].asBool();
		config->m_outlines.m_projectile_enemy_only = Load["m_outlines"]["m_projectile_enemy_only"].asBool();
		config->m_outlines.m_projectile_alpha = Load["m_outlines"]["m_projectile_alpha"].asFloat();

		config->m_outlines.m_world_outlines = Load["m_outlines"]["m_world_outlines"].asBool();
		config->m_outlines.m_world_alpha = Load["m_outlines"]["m_world_alpha"].asFloat();

		config->m_exploits.m_crithack = Load["m_exploits"]["m_crithack"].asBool();
		config->m_exploits.m_crithack_indicator = Load["m_exploits"]["m_crithack_indicator"].asBool();
		config->m_exploits.m_crithack_key.m_key = Load["m_exploits"]["m_crithack_key"].asInt();
		config->m_exploits.m_doubletap = Load["m_exploits"]["m_doubletap"].asBool();
		config->m_exploits.m_doubletap_indicator = Load["m_exploits"]["m_doubletap_indicator"].asBool();
		config->m_exploits.m_doubletap_in_air = Load["m_exploits"]["m_doubletap_in_air"].asBool();
		config->m_exploits.m_doubletap_recharge_key.m_key = Load["m_exploits"]["m_doubletap_recharge_key"].asInt();
		config->m_exploits.m_dynamic_warp_ticks = Load["m_exploits"]["m_dynamic_warp_ticks"].asInt();
		config->m_exploits.m_no_choke = Load["m_exploits"]["m_no_choke"].asBool();
		config->m_exploits.m_tickbase_warp_key.m_key = Load["m_exploits"]["m_tickbase_warp_key"].asInt();
		config->m_exploits.m_warp = Load["m_exploits"]["m_warp"].asBool();
		config->m_exploits.m_warp_speed = Load["m_exploits"]["m_warp_speed"].asInt();
		config->m_exploits.m_auto_warp = Load["m_exploits"]["m_auto_warp"].asBool();
		config->m_exploits.m_auto_warp_key.m_key = Load["m_exploits"]["m_auto_warp_key"].asInt();
		config->m_exploits.m_auto_warp_scale = Load["m_exploits"]["m_auto_warp_scale"].asInt();
		config->m_exploits.m_fake_latency = Load["m_exploits"]["m_fake_latency"].asBool();
		config->m_exploits.m_fake_latency_amount = Load["m_exploits"]["m_fake_latency_amount"].asFloat();
		config->m_exploits.m_backtrack = Load["m_exploits"]["m_backtrack"].asBool();

		config->m_misc.m_auto_strafer = Load["m_misc"]["m_auto_strafer"].asBool();
		config->m_misc.m_avoid_push = Load["m_misc"]["m_avoid_push"].asBool();
		config->m_misc.m_bunnyhop = Load["m_misc"]["m_bunnyhop"].asBool();
		config->m_misc.m_fast_stop = Load["m_misc"]["m_fast_stop"].asBool();
		config->m_misc.m_scout_jump = Load["m_misc"]["m_scout_jump"].asBool();
		config->m_misc.m_scout_jump_key = Load["m_misc"]["m_scout_jump_key"].asInt();
		config->m_misc.m_taunt_slide = Load["m_misc"]["m_taunt_slide"].asBool();
		config->m_misc.m_skip_welcome = Load["m_misc"]["m_skip_welcome"].asBool();
		config->m_misc.m_vote_revealer = Load["m_misc"]["m_vote_revealer"].asBool();
		config->m_misc.m_reduce_input_delay = Load["m_misc"]["m_reduce_input_delay"].asBool();
		config->m_misc.m_chat_player_connects = Load["m_misc"]["m_chat_player_connects"].asBool();
		config->m_misc.m_chat_player_disconnects = Load["m_misc"]["m_chat_player_disconnects"].asBool();
		config->m_misc.m_chat_player_class_changes = Load["m_misc"]["m_chat_player_class_changes"].asBool();
		config->m_misc.m_chat_player_name_changes = Load["m_misc"]["m_chat_player_name_changes"].asBool();
		config->m_misc.m_chat_vote_casts = Load["m_misc"]["m_chat_vote_casts"].asBool();

		config->m_projectile_aim.m_auto_shoot = Load["m_projectile_aim"]["m_auto_shoot"].asBool();
		config->m_projectile_aim.m_draw_prediction_path = Load["m_projectile_aim"]["m_draw_prediction_path"].asBool();
		config->m_projectile_aim.m_draw_projectile_path = Load["m_projectile_aim"]["m_draw_projectile_path"].asBool();
		config->m_projectile_aim.m_projectile_path_any_angle = Load["m_projectile_aim"]["m_projectile_path_any_angle"].asBool();
		config->m_projectile_aim.m_enabled = Load["m_projectile_aim"]["m_enabled"].asBool();
		config->m_projectile_aim.m_hitchance = Load["m_projectile_aim"]["m_hitchance"].asFloat();
		config->m_projectile_aim.m_max_simulation_time = Load["m_projectile_aim"]["m_max_simulation_time"].asFloat();
		config->m_projectile_aim.m_sample_time = Load["m_projectile_aim"]["m_sample_time"].asFloat();
		config->m_projectile_aim.m_optimized_prediction = Load["m_projectile_aim"]["m_optimized_prediction"].asBool();
		config->m_projectile_aim.m_turn_prediction = Load["m_projectile_aim"]["m_turn_prediction"].asBool();
		config->m_projectile_aim.m_target_sorting = Load["m_projectile_aim"]["m_target_sorting"].asInt();

		config->m_melee_aim.m_enable = Load["m_melee_aim"]["m_enable"].asBool();
		config->m_melee_aim.m_if_backstable = Load["m_melee_aim"]["m_if_backstable"].asBool();
		config->m_melee_aim.m_require_aimkey = Load["m_melee_aim"]["m_require_aimkey"].asBool();
		config->m_melee_aim.m_smack_friends = Load["m_melee_aim"]["m_smack_friends"].asBool();
		config->m_melee_aim.m_smack_friedly_buildings = Load["m_melee_aim"]["m_smack_friedly_buildings"].asBool();

		config->m_visuals.m_remove_recoil = Load["m_visuals"]["m_remove_recoil"].asBool();
		config->m_visuals.m_remove_scope = Load["m_visuals"]["m_remove_scope"].asBool();
		config->m_visuals.m_remove_zoom = Load["m_visuals"]["m_remove_zoom"].asBool();
		config->m_visuals.m_visualize_aimbot = Load["m_visuals"]["m_visualize_aimbot"].asBool();
		config->m_visuals.m_bullet_tracers = Load["m_visuals"]["m_bullet_tracers"].asInt();
		config->m_visuals.m_field_of_view = Load["m_visuals"]["m_field_of_view"].asFloat();
		config->m_visuals.m_mvm_giant_sounds = Load["m_visuals"]["m_mvm_giant_sounds"].asBool();
		config->m_visuals.m_sniper_sightlines = Load["m_visuals"]["m_sniper_sightlines"].asBool();
		config->m_visuals.m_thirdperson = Load["m_visuals"]["m_thirdperson"].asBool();
		config->m_visuals.m_thirdperson_key.m_key = Load["m_visuals"]["m_thirdperson_key"].asInt();
		config->m_visuals.m_viewmodel_roll = Load["m_visuals"]["m_viewmodel_roll"].asInt();
		config->m_visuals.m_viewmodel_sway = Load["m_visuals"]["m_viewmodel_sway"].asBool();
		config->m_visuals.m_viewmodel_sway_val = Load["m_visuals"]["m_viewmodel_sway_val"].asBool();
		config->m_visuals.m_viewmodel_x = Load["m_visuals"]["m_viewmodel_x"].asInt();
		config->m_visuals.m_viewmodel_y = Load["m_visuals"]["m_viewmodel_y"].asInt();
		config->m_visuals.m_viewmodel_z = Load["m_visuals"]["m_viewmodel_z"].asInt();
		config->m_visuals.m_viewmodel_fov = Load["m_visuals"]["m_viewmodel_fov"].asInt();
		config->m_visuals.m_aspect_ratio = Load["m_visuals"]["m_aspect_ratio"].asFloat();
		config->m_visuals.m_zoomed_field_of_view = Load["m_visuals"]["m_zoomed_field_of_view"].asInt();
		config->m_visuals.m_ragdolls_enabled = Load["m_visuals"]["m_ragdolls_enabled"].asBool();
		config->m_visuals.m_ragdolls_enemy_only = Load["m_visuals"]["m_ragdolls_enemy_only"].asBool();
		config->m_visuals.m_ragdoll_type = Load["m_visuals"]["m_ragdoll_type"].asInt();
		config->m_visuals.m_ragdoll_burning = Load["m_visuals"]["m_ragdoll_burning"].asBool();
		config->m_visuals.m_ragdoll_electrocuted = Load["m_visuals"]["m_ragdoll_electrocuted"].asBool();
		config->m_visuals.m_ragdoll_dissolving = Load["m_visuals"]["m_ragdoll_dissolving"].asBool();
		config->m_visuals.m_ragdoll_become_ash = Load["m_visuals"]["m_ragdoll_become_ash"].asBool();
		config->m_visuals.m_prop_alpha = Load["m_visuals"]["m_prop_alpha"].asFloat();

		config->m_visuals.m_projectile_camera = Load["m_visuals"]["m_projectile_camera"].asBool();
		config->m_visuals.m_projectile_camera_forward = Load["m_visuals"]["m_projectile_camera_forward"].asInt();
		config->m_visuals.m_projectile_camera_right = Load["m_visuals"]["m_projectile_camera_right"].asInt();
		config->m_visuals.m_projectile_camera_up = Load["m_visuals"]["m_projectile_camera_up"].asInt();
		config->m_visuals.m_projectile_camera_fov = Load["m_visuals"]["m_projectile_camera_fov"].asInt();

		visuals->camera_position.m_x = Load["m_visuals"]["camera_position.m_x"].asInt();
		visuals->camera_position.m_y = Load["m_visuals"]["camera_position.m_y"].asInt();
		visuals->camera_position.m_w = Load["m_visuals"]["camera_position.m_w"].asInt();
		visuals->camera_position.m_h = Load["m_visuals"]["camera_position.m_h"].asInt();

		config->m_hvh.m_fakelag = Load["m_hvh"]["m_fakelag"].asBool();
		config->m_hvh.m_break_lag_comp = Load["m_hvh"]["m_break_lag_comp"].asBool();
		config->m_hvh.m_max_ticks = Load["m_hvh"]["m_max_ticks"].asInt();
		config->m_hvh.m_max_unchoke_del = Load["m_hvh"]["m_max_unchoke_del"].asInt();
		config->m_hvh.m_fake_yaw.m_enabled = Load["m_hvh"]["m_fake_yaw.m_enabled"].asBool();
		config->m_hvh.m_fake_yaw.m_anti_logic = Load["m_hvh"]["m_fake_yaw.m_anti_logic"].asBool();
		config->m_hvh.m_fake_yaw.m_jitter = Load["m_hvh"]["m_fake_yaw.m_jitter"].asBool();
		config->m_hvh.m_fake_yaw.m_jitter_max = Load["m_hvh"]["m_fake_yaw.m_jitter_max"].asInt();
		config->m_hvh.m_fake_yaw.m_max_angle = Load["m_hvh"]["m_fake_yaw.m_max_angle"].asInt();
		config->m_hvh.m_fake_yaw.m_min_angle = Load["m_hvh"]["m_fake_yaw.m_min_angle"].asInt();
		config->m_hvh.m_real_yaw.m_enabled = Load["m_hvh"]["m_real_yaw.m_enabled"].asBool();
		config->m_hvh.m_real_yaw.m_anti_logic = Load["m_hvh"]["m_real_yaw.m_anti_logic"].asBool();
		config->m_hvh.m_real_yaw.m_edge = Load["m_hvh"]["m_real_yaw.m_edge"].asBool();
		config->m_hvh.m_pitch.m_enabled = Load["m_hvh"]["m_pitch.m_enabled"].asBool();
		config->m_hvh.m_pitch.m_jitter = Load["m_hvh"]["m_pitch.m_jitter"].asBool();
		config->m_hvh.m_pitch.m_jitter_max = Load["m_hvh"]["m_pitch.m_jitter_max"].asInt();
		config->m_hvh.m_pitch.m_max_angle = Load["m_hvh"]["m_pitch.m_max_angle"].asInt();
		config->m_hvh.m_pitch.m_min_angle = Load["m_hvh"]["m_pitch.m_min_angle"].asInt();

		config->m_menu.m_skull_background = Load["m_menu"]["m_skull_background"].asBool();

		load.close();
	}
}

void c_menu::run() {
	input->update();

	m_typing = false;
	static float change = 0.f;
	static int x = 0;
	static int y = 0;

	if (input->is_pressed(VK_INSERT) && !input->is_held(VK_INSERT) && util::is_window_in_focus()) {
		ctx->m_surface->set_cursor_visible(m_open = !m_open);
		change = ctx->m_engine_client->time();
		x = m_window.m_x;
		y = m_window.m_y;
	}

	m_fade_elapsed = ctx->m_engine_client->time() - change;

	if (m_fade_elapsed < m_fade_time) {
		m_fade_alpha = math::remap_val_clamped(m_fade_elapsed, 0.0f, m_fade_time, !m_open ? 1.0f : 0.0f, m_open ? 1.0f : 0.0f);
		m_window.m_x = math::remap_val_clamped(m_fade_elapsed, 0.0f, m_fade_time, !m_open ? x + 11 : x - 10, m_open ? x + 11 : x - 10);
		m_window.m_y = math::remap_val_clamped(m_fade_elapsed, 0.0f, m_fade_time, !m_open ? y + 11 : y - 10, m_open ? y + 11 : y - 10);
		ctx->m_surface->draw_set_alpha(m_fade_alpha);
	}

	if (m_open || m_fade_elapsed < m_fade_time) {
		input->drag(m_window.m_x, m_window.m_y, m_window.m_w, 20, 0);

		static std::string name = "";

		if (name.empty()) {
			name = "spook953paste v3";
			name += ctx->m_user_name;
		}

		render_window(name.c_str(), m_window, config->m_colors.m_ui_background, config->m_colors.m_ui_accent);

		m_last_tab = { m_window.m_x, m_window.m_y + 15, (int)(m_window.m_w * 0.2f), 20 };
		m_last_subtab = { m_window.m_x, m_window.m_y + 15 + 20, (int)(m_window.m_w * 0.25f), 15 };
		m_last_group = { m_window.m_x + 6, m_window.m_y + 40, 220, 0, };

		enable_clipping(m_window); {
			if (menu_tab("Aim", m_current_tab == TAB_AIM))
				m_current_tab = TAB_AIM;

			if (menu_tab("Visuals", m_current_tab == TAB_VISUALS))
				m_current_tab = TAB_VISUALS;

			if (menu_tab("HvH", m_current_tab == TAB_HVH))
				m_current_tab = TAB_HVH;

			if (menu_tab("Misc", m_current_tab == TAB_MISC))
				m_current_tab = TAB_MISC;

			if (menu_tab("Exploits", m_current_tab == TAB_EXPLOITS))
				m_current_tab = TAB_EXPLOITS;

			switch (m_current_tab) {
			case TAB_AIM: {
				render->line(m_window.m_x, m_window.m_y + 50, m_window.m_x + m_window.m_w, m_window.m_y + 50, config->m_colors.m_ui_accent);

				if (menu_subtab("Aimbot", m_aim_subtab == SUBTAB_AIMBOT))
					m_aim_subtab = SUBTAB_AIMBOT;

				if (menu_subtab("Automations", m_aim_subtab == SUBTAB_AUTOMATIONS))
					m_aim_subtab = SUBTAB_AUTOMATIONS;

				switch (m_aim_subtab) {
				case SUBTAB_AIMBOT: {
					menu_group_start(false, true, true); {
						check_box("Enable", config->m_aimbot_global.m_enabled);
						key_bind("Aim Key", config->m_aimbot_global.m_aim_key.m_key);
						check_box("Ignore Friends", config->m_aimbot_global.m_ignore_friends);
						check_box("Ignore Cloaked", config->m_aimbot_global.m_ignore_cloaked);
						slider_int("Aim FOV", config->m_aimbot_global.m_aim_fov, 0, 180, 1, "%i deg.");
					} menu_group("Global");

					menu_group_start(false, false, false); {
						check_box("Enable", config->m_aimbot.m_enabled);
						check_box("Require Aim Key", config->m_aimbot.m_require_key);
						check_box("Target Stickies", config->m_aimbot.m_aim_stickies);
						check_box("Boost DT Accuracy", config->m_aimbot.m_delayshot);
						slider_int("Minimum Hitchance", config->m_aimbot.m_delayshot_percent, 20, 50, 1, "%i%%");
						check_box("Auto Scope", config->m_aimbot.m_auto_scope);
						check_box("Body Aim If Lethal", config->m_aimbot.m_baim_on_lethal);
						check_box("Tap Fire", config->m_aimbot.m_tap_fire);
						slider_int("Tap Fire Distance", config->m_aimbot.m_tap_fire_distance, 200, 2000, 1, "%i hu");
						slider_float("Heavy Scale", config->m_aimbot.m_heavy_mp, 35.f, 80.f, 0.5f, "%.1f");
						slider_float("Scout Scale", config->m_aimbot.m_scout_mp, 30.f, 80.f, 0.5f, "%.1f");
						slider_float("Sniper Scale", config->m_aimbot.m_sniper_mp, 30.f, 80.f, 0.5f, "%.1f");
						check_box("Safe Points", config->m_aimbot.m_safe_point);
					} menu_group("Hitscan");

					menu_group_start(true, true, true); {
						check_box("Enable", config->m_projectile_aim.m_enabled);
						check_box("Auto Shoot", config->m_projectile_aim.m_auto_shoot);
						//	check_box( "Optimized Prediction", config->m_projectile_aim.m_optimized_prediction );
						check_box("Turn Prediction", config->m_projectile_aim.m_turn_prediction);
						slider_float("Sample Time", config->m_projectile_aim.m_sample_time, 0.05f, 0.2f, 0.01f, "%.2fs");
						slider_float("Minimum Hitchance", config->m_projectile_aim.m_hitchance, 0.0f, 100.0f, 1.0f, "%.0f%%");
						slider_float("Max Simulation Time", config->m_projectile_aim.m_max_simulation_time, 2.f, 10.f, 0.1f, "%.1fs");
					} menu_group("Projectile");

					menu_group_start(false, false, false); {
						check_box("Enable", config->m_melee_aim.m_enable);
						check_box("Require Aim Key", config->m_melee_aim.m_require_aimkey);
						check_box("Only if backstab", config->m_melee_aim.m_if_backstable);
						check_box("Auto Whip", config->m_melee_aim.m_smack_friends);
						check_box("Smack Own Buildings", config->m_melee_aim.m_smack_friedly_buildings);

					} menu_group("Melee");
					break;
				}

				case SUBTAB_AUTOMATIONS: {
					menu_group_start(false, true, true); {
						check_box("Enable", config->m_automations.m_enabled);
						check_box("Auto Detonate", config->m_automations.m_auto_detonate);
						slider_int("Auto Detonate Distance", config->m_automations.m_auto_detonate_distance, 30, 110, 1, "%i hu");
						slider_int("Max Sticky Charge", config->m_automations.m_charge_max, 0, 100);
					} menu_group("Automations");

					menu_group_start(true, true, true); {
						check_box("Auto Medic", config->m_automations.m_auto_vaccinator);
						check_box("Auto Pop Vacc", config->m_automations.m_auto_vacc_pop);
						slider_int("Projectile Threat", config->m_automations.m_auto_vaccinator_projectile_threat, 1, 3);
						slider_int("Projectile Prediction", config->m_automations.m_auto_vaccinator_projectile_prediction, 0, 6);
						slider_int("Player Threat", config->m_automations.m_auto_vaccinator_player_threat, 1, 3);
						slider_int("Healing Switch Delay", config->m_automations.m_auto_vac_switch_delay, 1, 60);
					} menu_group("Auto Medic");
					break;
				}
				default: break;
				}
				break;
			}

			case TAB_VISUALS: {
				render->line(m_window.m_x, m_window.m_y + 50, m_window.m_x + m_window.m_w, m_window.m_y + 50, config->m_colors.m_ui_accent);

				if (menu_subtab("ESP", m_visuals_subtab == SUBTAB_ESP))
					m_visuals_subtab = SUBTAB_ESP;

				if (menu_subtab("Models", m_visuals_subtab == SUBTAB_MODELS))
					m_visuals_subtab = SUBTAB_MODELS;

				if (menu_subtab("Outlines", m_visuals_subtab == SUBTAB_OUTLINES))
					m_visuals_subtab = SUBTAB_OUTLINES;

				if (menu_subtab("Misc", m_visuals_subtab == SUBTAB_MISC_))
					m_visuals_subtab = SUBTAB_MISC_;

				switch (m_visuals_subtab) {
				case SUBTAB_ESP: {
					menu_group_start(false, true, true); {
						check_box("Enable", config->m_esp.m_players_enabled);
						check_box("Player Box", config->m_esp.m_player_box);
						check_box("Player Name", config->m_esp.m_player_name);
						check_box("Player Health", config->m_esp.m_player_health);
						check_box("Player Flags", config->m_esp.m_player_flags);
						check_box("Player Weapon", config->m_esp.m_player_weapon);
						check_box("Player Team Color", config->m_esp.m_player_team_color);
						check_box("Player Enemy Only", config->m_esp.m_player_enemy);
						slider_int("Far ESP Timeout", config->m_esp.m_far_esp_fade_t, 0, 50);
						check_box("Out of FOV Arrows", config->m_esp.m_player_arrows);
						check_box("Arrows ESP", config->m_esp.m_arrows_esp);
						slider_float("Screen Distance", config->m_esp.m_arrows_screen_distance, 0.f, 0.25f);
						combo_box("Screen Shape", config->m_esp.m_arrows_screen_shape, { "Circle" , "Ellipsis" });
					} menu_group("Players");

					menu_group_start(false, false, false); {
						check_box("World ESP", config->m_esp.m_world_enabled);
						check_box("World Box", config->m_esp.m_world_box);
						check_box("World Name", config->m_esp.m_world_name);
						check_box("World Distance", config->m_esp.m_world_distance);
					} menu_group("World");

					menu_group_start(true, true, true); {
						check_box("Enable", config->m_esp.m_buildings_enabled);
						check_box("Building Box", config->m_esp.m_building_box);
						check_box("Building Name", config->m_esp.m_building_name);
						check_box("Building Health", config->m_esp.m_building_health);
						check_box("Building Flags", config->m_esp.m_building_flags);
						check_box("Building Enemy Only", config->m_esp.m_building_enemy);
					} menu_group("Buildings");

					menu_group_start(true, false, false); {
						check_box("Projectile ESP", config->m_esp.m_projectiles_enabled);
						check_box("Projectile Box", config->m_esp.m_projectile_box);
						check_box("Projectile Name", config->m_esp.m_projectile_name);
						check_box("Projectile Distance", config->m_esp.m_projectile_distance);
						check_box("Projectile Flags", config->m_esp.m_projectile_flags);
						check_box("Projectile Enemy Only", config->m_esp.m_projectile_enemy);
						check_box("Sticky Prediction", config->m_esp.m_predict_stickies);
					} menu_group("Projectiles");
					break;
				}

				case SUBTAB_MODELS: {
					menu_group_start(false, true, true); {
						check_box("Enable Models", config->m_models.m_enabled);
						combo_box("Rendering Order", config->m_models.m_rendering_order, { "Models On Top", "Outlines On Top" });
					} menu_group("Global");

					menu_group_start(false, false, false); {
						check_box("Player Models", config->m_models.m_player_models);
						check_box("Player Enemy Only", config->m_models.m_player_enemy_only);
						check_box("Two Models", config->m_models.m_player_two_models);
						if (config->m_models.m_player_two_models) {
							check_box("Overlay Visible", config->m_models.m_player_overlay_unoccluded);
							check_box("Overlay Hidden", config->m_models.m_player_overlay_occluded);
							combo_box("Visible", config->m_models.m_player_model_unoccluded, { "None", "Flat", "Shaded", "Fresnel" });
							combo_box("Hidden", config->m_models.m_player_model_occluded, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Alpha Visible", config->m_models.m_player_alpha_unoccluded, 0.0f, 1.0f);
							slider_float("Alpha Hidden", config->m_models.m_player_alpha_occluded, 0.0f, 1.0f);
						}
						else {
							check_box("Player Overlay", config->m_models.m_player_overlay);
							check_box("Ignore Z", config->m_models.m_player_ignorez);
							combo_box("Material", config->m_models.m_player_model, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Models Alpha", config->m_models.m_player_alpha, 0.0f, 1.0f);
						}
						check_box("Player Attachments", config->m_models.m_player_attachments);
						check_box("Player Backtrack", config->m_models.m_backtrack_models);
						check_box("Backtrack Last Tick", config->m_models.m_backtrack_last_only);
					} menu_group("Players");

					menu_group_start(false, false, false); {
						check_box("World Models", config->m_models.m_world_models);
						check_box("Two Models", config->m_models.m_world_two_models);
						if (config->m_models.m_world_two_models) {
							check_box("Overlay Visible", config->m_models.m_world_overlay_unoccluded);
							check_box("Overlay Hidden", config->m_models.m_world_overlay_occluded);
							combo_box("Visible", config->m_models.m_world_model_unoccluded, { "None", "Flat", "Shaded", "Fresnel" });
							combo_box("Hidden", config->m_models.m_world_model_occluded, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Alpha Visible", config->m_models.m_world_alpha_unoccluded, 0.0f, 1.0f);
							slider_float("Alpha Hidden", config->m_models.m_world_alpha_occluded, 0.0f, 1.0f);
						}
						else {
							check_box("World Overlay", config->m_models.m_world_overlay);
							check_box("Ignore Z", config->m_models.m_world_ignorez);
							combo_box("Material", config->m_models.m_world_model, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Models Alpha", config->m_models.m_world_alpha, 0.0f, 1.0f);
						}
					} menu_group("World");

					menu_group_start(true, true, true); {
						check_box("Building Models", config->m_models.m_building_models);
						check_box("Building Enemy Only", config->m_models.m_building_enemy_only);
						check_box("Two Models", config->m_models.m_building_two_models);
						if (config->m_models.m_building_two_models) {
							check_box("Overlay Visible", config->m_models.m_building_overlay_unoccluded);
							check_box("Overlay Hidden", config->m_models.m_building_overlay_occluded);
							combo_box("Visible", config->m_models.m_building_model_unoccluded, { "None", "Flat", "Shaded", "Fresnel" });
							combo_box("Hidden", config->m_models.m_building_model_occluded, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Alpha Visible", config->m_models.m_building_alpha_unoccluded, 0.0f, 1.0f);
							slider_float("Alpha Hidden", config->m_models.m_building_alpha_occluded, 0.0f, 1.0f);
						}
						else {
							check_box("Building Overlay", config->m_models.m_building_overlay);
							check_box("Ignore Z", config->m_models.m_building_ignorez);
							combo_box("Material", config->m_models.m_building_model, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Models Alpha", config->m_models.m_building_alpha, 0.0f, 1.0f);
						}
					} menu_group("Buildings");

					menu_group_start(true, false, false); {
						check_box("Projectile Models", config->m_models.m_projectile_models);
						check_box("Projectile Enemy Only", config->m_models.m_projectile_enemy_only);
						check_box("Two Models", config->m_models.m_projectile_two_models);
						if (config->m_models.m_projectile_two_models) {
							check_box("Overlay Visible", config->m_models.m_projectile_overlay_unoccluded);
							check_box("Overlay Hidden", config->m_models.m_projectile_overlay_occluded);
							combo_box("Visible", config->m_models.m_projectile_model_unoccluded, { "None", "Flat", "Shaded", "Fresnel" });
							combo_box("Hidden", config->m_models.m_projectile_model_occluded, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Alpha Visible", config->m_models.m_projectile_alpha_unoccluded, 0.0f, 1.0f);
							slider_float("Alpha Hidden", config->m_models.m_projectile_alpha_occluded, 0.0f, 1.0f);
						}
						else {
							check_box("Projectile Overlay", config->m_models.m_projectile_overlay);
							check_box("Ignore Z", config->m_models.m_projectile_ignorez);
							combo_box("Material", config->m_models.m_projectile_model, { "None", "Flat", "Shaded", "Fresnel" });
							slider_float("Models Alpha", config->m_models.m_projectile_alpha, 0.0f, 1.0f);
						}
					} menu_group("Projectiles");
					break;
				}

				case SUBTAB_OUTLINES: {
					menu_group_start(false, true, true); {
						check_box("Enable Outlines", config->m_outlines.m_enabled);
						check_box("Blur Outline", config->m_outlines.m_blur_outline);
						slider_int("Blur Scale", config->m_outlines.m_blur_scale, 1, 10);
						check_box("Stencil Outline", config->m_outlines.m_stencil_outline);
						slider_int("Stencil Scale", config->m_outlines.m_stencil_scale, 1, 5);
					} menu_group("Global");

					menu_group_start(false, false, false); {
						check_box("Enable", config->m_outlines.m_player_outlines);
						check_box("Enemy Only", config->m_outlines.m_player_enemy_only);
						slider_float("Player Alpha", config->m_outlines.m_player_alpha, 0.0f, 1.0f, 0.1f);
					} menu_group("Players");

					menu_group_start(false, false, false); {
						check_box("World Outlines", config->m_outlines.m_world_outlines);
						slider_float("World Alpha", config->m_outlines.m_world_alpha, 0.0f, 1.0f, 0.1f);
					} menu_group("World");

					menu_group_start(true, true, true); {
						check_box("Enable", config->m_outlines.m_building_outlines);
						check_box("Enemy Only", config->m_outlines.m_building_enemy_only);
						slider_float("Building Alpha", config->m_outlines.m_building_alpha, 0.0f, 1.0f, 0.1f);
					} menu_group("Buildings");

					menu_group_start(true, false, false); {
						check_box("Projectile Outlines", config->m_outlines.m_projectile_outlines);
						check_box("Projectile Enemy Only", config->m_outlines.m_projectile_enemy_only);
						slider_float("Projectile Alpha", config->m_outlines.m_projectile_alpha, 0.0f, 1.0f, 0.1f);
					} menu_group("Projectiles");
					break;
				}

				case SUBTAB_MISC_: {
					menu_group_start(false, true, true); {
						combo_box("Bullet Tracers", config->m_visuals.m_bullet_tracers, { "Default", "CAPPER", "Machina", "W-Machina", "Zap", "Zap 2", "Ink" });
						check_box("MvM Sound Replacement", config->m_visuals.m_mvm_giant_sounds);
						check_box("Sniper Sightlines", config->m_visuals.m_sniper_sightlines);
						check_box("Draw Prediction Path", config->m_projectile_aim.m_draw_prediction_path);
						check_box("Draw Projectile Path", config->m_projectile_aim.m_draw_projectile_path);
						check_box("Remove Recoil", config->m_visuals.m_remove_recoil);
						check_box("Remove Scope", config->m_visuals.m_remove_scope);
						check_box("Remove Zoom", config->m_visuals.m_remove_zoom);
						slider_float("Prop Alpha", config->m_visuals.m_prop_alpha, 0.0f, 1.0f, 0.05f);
						key_bind("Thirdperson Key", config->m_visuals.m_thirdperson_key.m_key);
						check_box("Totenkopf Background", config->m_menu.m_skull_background);
					} menu_group("Misc");

					menu_group_start(false, false, false); {
						check_box("Enabled", config->m_visuals.m_ragdolls_enabled);
						if (config->m_visuals.m_ragdolls_enabled) {
							check_box("Enemy Only", config->m_visuals.m_ragdolls_enemy_only);
							combo_box("Ragdoll Type", config->m_visuals.m_ragdoll_type, { "Default", "Gold", "Ice" });
							// TODO: Replace these with a multi-combo!
							multi_combo_box("Ragdoll Effects", { { "Burning", &config->m_visuals.m_ragdoll_burning },
											 { "Electrocuted", &config->m_visuals.m_ragdoll_electrocuted },
											 { "Dissolving", &config->m_visuals.m_ragdoll_dissolving },
											 { "Become Ash", &config->m_visuals.m_ragdoll_become_ash } });
							/*check_box( "Burning", config->m_visuals.m_ragdoll_burning );
							check_box( "Electrocuted", config->m_visuals.m_ragdoll_electrocuted );
							check_box( "Dissolving", config->m_visuals.m_ragdoll_dissolving );
							check_box( "Become Ash", config->m_visuals.m_ragdoll_become_ash );*/
						}
					} menu_group("Ragdolls");

					menu_group_start(false, false, false); {
						slider_int("Field of View", config->m_visuals.m_field_of_view, 0, 120);
						slider_int("Zoomed FOV", config->m_visuals.m_zoomed_field_of_view, 0, 120);
						slider_float("Aspect Ratio", config->m_visuals.m_aspect_ratio, 0.f, 2.f, 0.1f);
					} menu_group("View");

					menu_group_start(true, true, true); {
						check_box("Visualize Aimbot", config->m_visuals.m_visualize_aimbot);
						check_box("Sway", config->m_visuals.m_viewmodel_sway);
						slider_int("Sway Scale", config->m_visuals.m_viewmodel_sway_val, 1, 10);
						slider_int("Yaw", config->m_visuals.m_viewmodel_x, -20, 20);
						slider_int("Forward", config->m_visuals.m_viewmodel_y, -20, 20);
						slider_int("Pitch", config->m_visuals.m_viewmodel_z, -20, 20);
						slider_int("Roll", config->m_visuals.m_viewmodel_roll, -180, 180);
						slider_int("FOV", config->m_visuals.m_viewmodel_fov, 0, 140);
					} menu_group("Viewmodel");

					menu_group_start(true, false, false); {
						check_box("Projectile Trajectory", config->m_projectile_aim.m_projectile_path_any_angle);
						if (config->m_projectile_aim.m_projectile_path_any_angle) {
							check_box("Projectile Camera", config->m_visuals.m_projectile_camera);
							if (config->m_visuals.m_projectile_camera) {
								slider_int("Offset Forwards", config->m_visuals.m_projectile_camera_forward, -150, 150);
								slider_int("Offset Right", config->m_visuals.m_projectile_camera_right, -150, 150);
								slider_int("Offset Upwards", config->m_visuals.m_projectile_camera_up, -150, 150);
								slider_int("Camera FOV", config->m_visuals.m_projectile_camera_fov, 30, 120);
								slider_int("Camera Width", visuals->camera_position.m_w, 200, 400);
								slider_int("Camera Height", visuals->camera_position.m_h, 100, 300);
							}
						}
					} menu_group("Projectile Visualizer");
					break;
				}
				default: break;
				}
				break;
			}

			case TAB_MISC: {
				menu_group_start(false, true, false); {
					check_box("Bunnyhop", config->m_misc.m_bunnyhop);
					check_box("Auto Strafe", config->m_misc.m_auto_strafer);
					check_box("Fast Stop", config->m_misc.m_fast_stop);
					check_box("Scout Jump", config->m_misc.m_scout_jump);
					key_bind("Scout Jump Key", config->m_misc.m_scout_jump_key.m_key);
					check_box("Taunt Slide", config->m_misc.m_taunt_slide);
					check_box("Avoid Pushaway", config->m_misc.m_avoid_push);
				} menu_group("Movement");

				menu_group_start(true, true, false); {
					button("Save Config", [&]() { save_config(); });
					button("Load Config", [&]() { load_config(); });
					button("Dump Players", [&]() { dump_server_players(); });
				} menu_group("Configs");

				menu_group_start(false, false, false); {
					check_box("Skip welcome", config->m_misc.m_skip_welcome);
					check_box("Reveal Enemy Votes", config->m_misc.m_vote_revealer);
					check_box("Reduce Input Delay", config->m_misc.m_reduce_input_delay);
					button("No Restrictions", [&]() { no_restrictions(); });
					button("Kill Interp", [&]() { kill_interp(); });
				} menu_group("Other");

				menu_group_start(true, false, false); {
					check_box("Player Connects", config->m_misc.m_chat_player_connects);
					check_box("Player Disconnects", config->m_misc.m_chat_player_disconnects);
					check_box("Player Class Changes", config->m_misc.m_chat_player_class_changes);
					check_box("Player Name Changes", config->m_misc.m_chat_player_name_changes);
					check_box("Vote Casts", config->m_misc.m_chat_vote_casts);
				} menu_group("Chat Flags");
				break;
			}

			case TAB_HVH: {
				render->line(m_window.m_x, m_window.m_y + 50, m_window.m_x + m_window.m_w, m_window.m_y + 50, config->m_colors.m_ui_accent);

				if (menu_subtab("Anti-Aim", m_hvh_subtab == SUBTAB_ANTIAIM)) {
					m_hvh_subtab = SUBTAB_ANTIAIM;
				}

				if (menu_subtab("Fakelag", m_hvh_subtab == SUBTAB_FAKELAG)) {
					m_hvh_subtab = SUBTAB_FAKELAG;
				}

				switch (m_hvh_subtab) {
				case SUBTAB_ANTIAIM: {
					menu_group_start(false, true, true); {
						check_box("Enabled", config->m_hvh.m_pitch.m_enabled);
						check_box("Jitter", config->m_hvh.m_pitch.m_jitter);
						if (config->m_hvh.m_pitch.m_jitter) {
							slider_int("Jitter Delay", config->m_hvh.m_pitch.m_jitter_max, 10, 250, 1);
							slider_int("First Angle", config->m_hvh.m_pitch.m_min_angle, -271, 271);
							slider_int("Second Angle", config->m_hvh.m_pitch.m_max_angle, -271, 271);
						}
						else slider_int("Angle", config->m_hvh.m_pitch.m_pitch_angle, -271, 271);
					} menu_group("Pitch");

					menu_group_start(true, true, true); {
						check_box("Enabled", config->m_hvh.m_fake_yaw.m_enabled);
						check_box("Anti Logic", config->m_hvh.m_fake_yaw.m_anti_logic);
						check_box("Jitter", config->m_hvh.m_fake_yaw.m_jitter);
						slider_int("Jitter Angles", config->m_hvh.m_fake_yaw.m_jitter_max, 1, 12, 1);
						slider_int("Minimum Angle", config->m_hvh.m_fake_yaw.m_min_angle, -180, 0, 1);
						slider_int("Maximum Angle", config->m_hvh.m_fake_yaw.m_max_angle, 0, 180, 1);
					} menu_group("Fake Yaw");

					menu_group_start(false, false, false); {
						check_box("Enabled", config->m_hvh.m_real_yaw.m_enabled);
						check_box("Anti Logic", config->m_hvh.m_real_yaw.m_anti_logic);
						check_box("Edge", config->m_hvh.m_real_yaw.m_edge);
					} menu_group("Real Yaw");
					break;
				}

				case SUBTAB_FAKELAG: {
					menu_group_start(false, true, true); {
						check_box("Enable", config->m_hvh.m_fakelag);
						check_box("Break Lag-Comp", config->m_hvh.m_break_lag_comp);
						slider_int("Max Ticks", config->m_hvh.m_max_ticks, 10, 22);
						slider_int("Max Unchoke Delay", config->m_hvh.m_max_unchoke_del, 0, 10);
					} menu_group("Fakelag");
					break;
				}
				}
				break;
			}

			case TAB_EXPLOITS: {
				menu_group_start(false, true, false); {
					check_box("Enable", config->m_exploits.m_crithack);
					check_box("Draw Indicator", config->m_exploits.m_crithack_indicator);
					key_bind("Force Crits Key", config->m_exploits.m_crithack_key.m_key);
				} menu_group("Crits");

				menu_group_start(false, false, false); {
					check_box("Enable", config->m_exploits.m_backtrack);
					check_box("Fake Latency", config->m_exploits.m_fake_latency);
					slider_int("Fake Latency Amount", config->m_exploits.m_fake_latency_amount, 0, 800, 10, "%i ms");
				} menu_group("Backtrack");

#ifndef JW_RELEASE_BUILD
				menu_group_start(false, false, false); {
					check_box("Enable", config->m_seed_pred.m_enabled);
					check_box("Draw Indicator", config->m_seed_pred.m_draw_indicator);
				} menu_group("Hitscan Nospread");
#endif

				menu_group_start(true, true, false); {
					check_box("Enable Doubletap", config->m_exploits.m_doubletap);
					check_box("Draw Indicator", config->m_exploits.m_doubletap_indicator);
					key_bind("Recharge Key", config->m_exploits.m_doubletap_recharge_key.m_key);
					check_box("Shift in air", config->m_exploits.m_doubletap_in_air);
					check_box("Warp", config->m_exploits.m_warp);
					check_box("Dynamic Warp", config->m_exploits.m_dynamic_warp_ticks);
					slider_int("Ticks per Warp", config->m_exploits.m_warp_speed, 1, 22, 1, "%i");
					key_bind("Warp Key", config->m_exploits.m_tickbase_warp_key.m_key);
					check_box("Auto Warp", config->m_exploits.m_auto_warp);
					slider_int("Auto Warp Scale", config->m_exploits.m_auto_warp_scale, 10, 50, 10);
					key_bind("Auto Warp Key", config->m_exploits.m_auto_warp_key.m_key);
				} menu_group("Tickbase");
				break;
			}
			} update_combo(); update_multi_combo();
		} disable_clipping();
	} ctx->m_surface->draw_set_alpha(1.0f);
}

void c_menu::reset() {
	if (m_open) {
		if (backup_ecx && backup_edx)
			hooks::lock_cursor::original_function(backup_ecx, backup_edx);

		ctx->m_surface->set_cursor_visible(false);
		m_open = false;
	}

	if (hooks::wnd_proc::original_wndproc)
		SetWindowLongW(hooks::wnd_proc::game_hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(hooks::wnd_proc::original_wndproc));
}