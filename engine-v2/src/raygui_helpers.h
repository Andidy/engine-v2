#pragma once

#ifndef RAYGUI_H
#include "raygui.h"
#endif

#include <string>

namespace gui {
	struct ButtonContext {
		Rectangle bounds;
		std::string text;
	};

	bool Button(ButtonContext& bc);

	struct LineContext {
		Rectangle bounds;
		std::string text;
	};

	void Line(LineContext& lc);

	struct CheckBoxContext {
		Rectangle bounds;
		std::string text;
		bool checked;
	};

	bool CheckBox(CheckBoxContext& cbc);

	struct TextBoxContext {
		Rectangle bounds;
		size_t text_size;
		char* text;
		bool edit_mode;
	};

	void TextBox(TextBoxContext& tbc);

	struct ColorPickerContext {
		Rectangle bounds;
		Color color;
	};

	Color ColorPicker(ColorPickerContext& cpc);

	struct SpinnerContext {
		Rectangle bounds;
		std::string text;
		bool edit_mode;
		int value;
		int min;
		int max;
	};

	void Spinner(SpinnerContext& sc);
	void Spinner(SpinnerContext& sc, int max);

	struct WindowBoxContext {
		Rectangle bounds;
		std::string text;
		bool is_active;
	};

	void WindowBox(WindowBoxContext& wbc);

	struct LabelContext {
		Rectangle bounds;
		std::string text;
	};

	void Label(LabelContext& lc);

	struct ValueBoxContext {
		Rectangle bounds;
		std::string text;
		bool edit_mode;
		int value;
		int min;
		int max;
	};

	void ValueBox(ValueBoxContext& vbc);
};