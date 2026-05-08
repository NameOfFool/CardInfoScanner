#ifndef CARDSEARCHER_IMAGE_SCANNER_PARSER_HPP
#define CARDSEARCHER_IMAGE_SCANNER_PARSER_HPP
#include <qfile.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "iscanner_parser.hpp"


class ImageScannerParser : public IScannerParser {
public:
    void parseFile(const QString &filePath, std::function<void(const QString &, const QString &)> onParsed) override {
        tesseract::TessBaseAPI api;

        if (api.Init(nullptr, "eng")) {
            throw std::runtime_error("Tesseract init failed");
        }

        Pix *image = pixRead(filePath.toStdString().c_str());
        api.SetImage(image);

        const char *outText = api.GetUTF8Text();
        const QString result(outText);

        delete[] outText;
        pixDestroy(&image);

        onParsed(result, filePath);
    }
};


#endif //CARDSEARCHER_IMAGE_SCANNER_PARSER_HPP
