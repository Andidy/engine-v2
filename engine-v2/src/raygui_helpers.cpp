#include "raygui_helpers.h"

namespace gui {
	void Button::Draw() {
		pressed = GuiButton(bounds, text.c_str());
	}
	
	void Line::Draw() {
		GuiLine(bounds, text.c_str());
	}

	void CheckBox::Draw() {
		checked = GuiCheckBox(bounds, text.c_str(), checked);
	}

	void TextBox::Draw() {
		if (GuiTextBox(bounds, text, text_size, edit_mode)) {
			edit_mode = !edit_mode;
		}
	}

	void ColorPicker::Draw() {
		color = GuiColorPicker(bounds, color);
	}

	void Spinner::Draw() {
		if (GuiSpinner(bounds, text.c_str(), &value, min, max, edit_mode)) {
			edit_mode = !edit_mode;
		}
	}

	void Spinner::Draw(int max) {
		max = max;
		if (GuiSpinner(bounds, text.c_str(), &value, min, max, edit_mode)) {
			edit_mode = !edit_mode;
		}
	}

	void WindowBox::Draw() {
		is_active = !GuiWindowBox(bounds, text.c_str());
	}

	void Label::Draw() {
		GuiLabel(bounds, text.c_str());
	}

	void ValueBox::Draw() {
		if (GuiValueBox(bounds, text.c_str(), &value, min, max, edit_mode)) {
			edit_mode = !edit_mode;
		}
	}
}