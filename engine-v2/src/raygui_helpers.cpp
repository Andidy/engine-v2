#include "raygui_helpers.h"

namespace gui {
	bool Button(ButtonContext& bc) {
		return GuiButton(bc.bounds, bc.text.c_str());
	}
	
	void Line(LineContext& lc) {
		GuiLine(lc.bounds, lc.text.c_str());
	}

	bool CheckBox(CheckBoxContext& cbc) {
		cbc.checked = GuiCheckBox(cbc.bounds, cbc.text.c_str(), cbc.checked);
		return cbc.checked;
	}

	void TextBox(TextBoxContext& tbc) {
		if (GuiTextBox(tbc.bounds, tbc.text, tbc.text_size, tbc.edit_mode)) {
			tbc.edit_mode = !tbc.edit_mode;
		}
	}

	Color ColorPicker(ColorPickerContext& cpc) {
		cpc.color = GuiColorPicker(cpc.bounds, cpc.color);
		return cpc.color;
	}

	void Spinner(SpinnerContext& sc) {
		if (GuiSpinner(sc.bounds, sc.text.c_str(), &sc.value, sc.min, sc.max, sc.edit_mode)) {
			sc.edit_mode = !sc.edit_mode;
		}
	}

	void Spinner(SpinnerContext& sc, int max) {
		sc.max = max;
		if (GuiSpinner(sc.bounds, sc.text.c_str(), &sc.value, sc.min, sc.max, sc.edit_mode)) {
			sc.edit_mode = !sc.edit_mode;
		}
	}

	void WindowBox(WindowBoxContext& wbc) {
		wbc.is_active = !GuiWindowBox(wbc.bounds, wbc.text.c_str());
	}

	void Label(LabelContext& lc) {
		GuiLabel(lc.bounds, lc.text.c_str());
	}

	void ValueBox(ValueBoxContext& vbc) {
		if (GuiValueBox(vbc.bounds, vbc.text.c_str(), &vbc.value, vbc.min, vbc.max, vbc.edit_mode)) {
			vbc.edit_mode = !vbc.edit_mode;
		}
	}
}