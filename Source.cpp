//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2020 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementReader.h>
#include <PDF/Element.h>
#include <PDF/Font.h>
#include <Filters/FilterReader.h>
#include <PDF/Image/Image2RGB.h>
#include <PDF/TextExtractor.h>

// This sample illustrates the basic text extraction capabilities of PDFNet.
#include <fstream>
#include <iostream>

using namespace std;

using namespace pdftron;
using namespace PDF;
using namespace SDF;
using namespace Common;
using namespace Filters;

// A utility method used to dump all text content in the console window.
void DumpAllText(ElementReader& reader)
{
	Element element;
	while ((element = reader.Next()) != 0)
	{
		switch (element.GetType())
		{
		case Element::e_text_begin:
			cout << "\n--> Text Block Begin\n";
			break;
		case Element::e_text_end:
			cout << "\n--> Text Block End\n";
			break;
		case Element::e_text:
		{
			Rect bbox;
			element.GetBBox(bbox);
			cout << "\n--> BBox: " << bbox.x1 << ", "
				<< bbox.y1 << ", "
				<< bbox.x2 << ", "
				<< bbox.y2 << "\n";

			UString arr = element.GetTextString();
			cout << arr << "\n";
		}
		break;
		case Element::e_text_new_line:
			cout << "\n--> New Line\n";
			break;
		case Element::e_form:				// Process form XObjects
			reader.FormBegin();
			DumpAllText(reader);
			reader.End();
			break;
		}
	}
}

// A helper method for ReadTextFromRect
void RectTextSearch(ElementReader& reader, const Rect& pos, UString& srch_str)
{
	Element element;
	while (element = reader.Next())
	{
		switch (element.GetType())
		{
		case Element::e_text:
		{
			Rect bbox;
			element.GetBBox(bbox);
			if (bbox.IntersectRect(bbox, pos))
			{
				UString arr = element.GetTextString();
				srch_str += arr;
				srch_str += "\n"; // add a new line?
			}
			break;
		}
		case Element::e_text_new_line:
		{
			break;
		}
		case Element::e_form: // Process form XObjects
		{
			reader.FormBegin();
			RectTextSearch(reader, pos, srch_str);
			reader.End();
			break;
		}
		}
	}
}

// A utility method used to extract all text content from
// a given selection rectangle. The rectangle coordinates are
// expressed in PDF user/page coordinate system.
UString ReadTextFromRect(Page& page, const Rect& pos, ElementReader& reader)
{
	UString srch_str;
	reader.Begin(page);
	RectTextSearch(reader, pos, srch_str);
	reader.End();
	return srch_str;
}


void PrintStyle(TextExtractor::Style& s)
{
	UInt8 rgb[3];
	char rgb_hex[24];

	s.GetColor(rgb);
	//sprintf(rgb_hex, "%02X%02X%02X;", rgb[0], rgb[1], rgb[2]);
	cout << " style=\"font-family:" << s.GetFontName() << "; " << "font-size:" << s.GetFontSize() << ";"
		<< (s.IsSerif() ? " sans-serif; " : " ") << "color:#" << rgb_hex << "\"";
}

int main(int argc, char *argv[])
{
	int ret = 0;
	PDFNet::Initialize();
	// Relative path to the folder containing test files.
	string input_path = "sample.pdf";
	// string output_path = "../../TestFiles/Output/";
	ofstream file;
	file.open("text.txt");



	const char* filein = argc > 1 ? argv[1] : input_path.c_str();

	bool example1_basic = true;
	bool example2_xml = false;
	bool example3_wordlist = false;
	bool example4_advanced = true;
	bool example5_low_level = false;

	// Sample code showing how to use high-level text extraction APIs.

		PDFDoc doc(filein);
		doc.InitSecurityHandler();
		int i = 1;
		Page page = doc.GetPage(i);
		while (page)
		{
			if (!page) {
				cout << "Page not found." << endl;
				return 1;
			}

			TextExtractor txt;
			txt.Begin(page); // Read the page.
			// Other options you may want to consider...
			// txt.Begin(*itr, 0, TextExtractor::e_no_dup_remove);
			// txt.Begin(*itr, 0, TextExtractor::e_remove_hidden_text);


			// Example 1. Get all text on the page in a single string.
			// Words will be separated with space or new line characters.
			if (example1_basic)
			{
				// Get the word count.
				cout << "Word Count: " << txt.GetWordCount() << endl;

				UString text;
				txt.GetAsText(text);
				cout << "\n\n- GetAsText --------------------------\n" << text << endl;
				cout << "-----------------------------------------------------------" << endl;
			}
			i++;
			page = doc.GetPage(i);
		}
	PDFNet::Terminate();
	return ret;
}