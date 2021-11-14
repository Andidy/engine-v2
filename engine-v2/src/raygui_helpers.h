#pragma once

#ifndef RAYGUI_H
#include "raygui.h"
#endif

#include <string>

namespace gui {
	struct Element {
		virtual void Draw() = 0;
	};
	
	struct Button : Element {
		Rectangle bounds;
		std::string text;
		bool pressed;

		void Draw();
	};

	struct Line : Element {
		Rectangle bounds;
		std::string text;

		void Draw();
	};

	struct CheckBox : Element {
		Rectangle bounds;
		std::string text;
		bool checked;

		void Draw();
	};

	struct TextBox : Element {
		Rectangle bounds;
		size_t text_size;
		char* text;
		bool edit_mode;

		void Draw();
	};

	struct ColorPicker : Element {
		Rectangle bounds;
		Color color;

		void Draw();
	};

	struct Spinner : Element {
		Rectangle bounds;
		std::string text;
		bool edit_mode;
		int value;
		int min;
		int max;

		void Draw();
		void Draw(int max);
	};

	struct WindowBox : Element {
		Rectangle bounds;
		std::string text;
		bool is_active;

		void Draw();
	};

	struct Label : Element {
		Rectangle bounds;
		std::string text;

		void Draw();
	};

	struct ValueBox : Element {
		Rectangle bounds;
		std::string text;
		bool edit_mode;
		int value;
		int min;
		int max;

		void Draw();
	};
};