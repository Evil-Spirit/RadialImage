//---------------------------------------------------------------------------

#ifndef RadialImageH
#define RadialImageH

//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <stdio.h>

//---------------------------------------------------------------------------

#define SBP_MAGIC '0' << 24 | 'P' << 16 | 'B' << 8 | 'S'


class Bits {
	unsigned char *data;
	int size;

	void clear() {
		delete [] data;
		size = 0;
		data = NULL;
	}

public:

	Bits() : data(NULL) {
		clear();
	}

	Bits(const Bits &o) : data(NULL) {
		clear();
        *this = o;
	}

	Bits(int size) : data(NULL) {
		setSize(size);
	}

	~Bits() {
		clear();
	}

    Bits &operator =(const Bits &o) {
    	setSize(o.getSize());
        memcpy(data, o.data, size);
        return *this;
    }

	void setSize(int size) {
		clear();
		this->size = size;
		data = new unsigned char[this->size];
		memset(data, 0, this->size * sizeof(unsigned char));
	}

	int getSize() {
		return size;
	}

	bool operator[](int index) {
		return getBit(index);
	}


	void setByte(int index, int byte) {
		data[index] = byte;
	}

	int getByte(int index) {
		return data[index];
	}

	void setBit2(int index, bool bit) {
		int i = index / 8;
		int j = index % 8;
		if (bit) {
			data[i] |= 0x01 << (7 - j);
		} else {
			data[i] &= ~(0x01 << (7 - j));
		}
	}

	void setBit(int index, bool bit) {
		int i = index / 8;
		int j = index % 8;
		if (bit) {
			data[i] |= 0x01 << j;
		} else {
			data[i] &= ~(0x01 << j);
		}
	}

	bool getBit(int index) {
		int i = index / 8;
		int j = index % 8;
		return (data[i] >> j ) & 0x01;
	}

	bool getBit2(int index) {
		int i = index / 8;
		int j = index % 8;
		return (data[i] >> (7 - j) ) & 0x01;
	}

    unsigned char *getData() {
    	return data;
    }
};

class RadialImage {

	Bits *data;
	int count;
	int lights;
	int hole;

	TColor color;

	void clear() {
		delete [] data;
		count = 0;
		lights = 0;
		data = NULL;
	}

public:

    void turn(int turn_sectors) {

        
		Bits *new_data = new Bits[count];

        for (int i = 0; i<count; i++) {
        	new_data[(i + 2 * count + turn_sectors) % count] = data[i];
        }

        delete [] data;
        data = new_data;
        
        
    }
    
	RadialImage() : data(NULL) {
		color = clBlue;
		clear();
	}

	~RadialImage() {
		clear();
	}

	void setHole(int percent) {
		hole = percent;
	}

	int getHole() const {
		return hole;
	}

	void setSize(int c, int l) {
		clear();

		count = c;
		lights = l;

		data = new Bits[count];
		for (int i=0; i<count; i++) {
			data[i].setSize(lights / 8);
		}
	}

	int getCount() const {
		return count;
	}

	int getLights() const {
		return lights;
	}

	Bits &operator[](int index) {
		return data[index];
	}

	void convert(TImage *image) {
		float cx = image->Canvas->ClipRect.Width() - 1;
		float cy = image->Canvas->ClipRect.Height() - 1;

		int sx = 2;
		int sy = 2;

		float ratio = float(hole) / 100;
		for (int j=0; j<lights; j++) {
			for (int i=0; i<count; i++) {
				float angle = 2 * M_PI / count * i - M_PI / 2;
				int x = (cos(angle) * (cx * (j + 1) / lights * (1 - ratio) + cx * ratio) + cx) / 2;
				int y = (sin(angle) * (cy * (j + 1) / lights * (1 - ratio) + cy * ratio) + cy) / 2;
				bool bit = (image->Canvas->Pixels[x][y] >> 16) & 0xFF > 128;
				data[i].setBit(j, bit);
			}
		}
	}

    int prepareString(AnsiString &def, AnsiString &s) {

		int pos = 0;
		if ((pos = s.Pos(def)) == 0) return 0;
        s.Delete(pos, def.Length());

        while ((pos = s.Pos(' ')) != 0) s.Delete(pos, 1);
        while ((pos = s.Pos('\t')) != 0) s.Delete(pos, 1);
        while ((pos = s.Pos('\n')) != 0) s.Delete(pos, 1);

        if (s == "") return 0;
        if (s[1] == ';') return 0;

        while ((pos = s.Pos('b')) != 0) s.Delete(pos, 1);
        while ((pos = s.Pos(',')) != 0) s.Delete(pos, 1);

        return s.Length();
        
    }

	bool convertANY_BSP(const AnsiString &name, const char *def) {

		FILE *file = fopen(name.c_str(), "r");
		if (!file) return false;

		char str[4096];

        int sectors_count = 0;
        int lights_count = 0;

		while (fgets(str, 4096, file)) {

			AnsiString s = str;

            int lc = prepareString(def, s);
            if (lc == 0) continue;

            if (sectors_count == 0) {
				lights_count = lc;
            } else {
            	if (lc != lights_count) {
					fclose(file);
		            return false;
                }
           	}
            
            sectors_count ++;
        }

        this->setSize(sectors_count, lights_count);
        
        fseek(file, 0, SEEK_SET);

		int countI = 0;

		while (fgets(str, 4096, file)) {
			AnsiString s = str;

            if (prepareString(def, s) == 0) continue;

			for (int i=1; i<=s.Length(); i++) {
				bool bit = !(StrToInt(s[i]));
				data[countI].setBit2(i - 1, bit);
			}

			countI ++;
		}

		fclose(file);
        return true;
	}

	void convertBSP(const AnsiString &name) {
    	convertANY_BSP(name, "DB");
	}

	void convertBSP_OLD(const AnsiString &name) {
    	convertANY_BSP(name, ".DCB");
	}
    

	void saveBSP_OLD(const AnsiString &name) {
		FILE *file = fopen(name.c_str(), "w");
		if (!file) return;

		fprintf(file, ".TITL 'Radial Image'\n");
		fprintf(file, ".STITL 'Radial Image Editor, Copyright (c) Alexei Egorov aka FadeToBlack, 2008'\n");
		fprintf(file, ".LSTOUT -\n");

		AnsiString s;
		for (int i=0; i<count; i++) {
			fprintf(file, ".DCB ");
			for (int j=0; j<lights; j++) {
				s = IntToStr(1 - data[i].getBit2(j));
				fprintf(file, s.c_str());
				if ((j + 1) % 8 == 0 && j != lights - 1) {
					fprintf(file, "b, ");
				}
			}
			fprintf(file, "b\n");
		}

		fprintf(file, ".LSTOUT .\n");

		fclose(file);

	}

	void saveBSP(const AnsiString &name) {
		FILE *file = fopen(name.c_str(), "w");
		if (!file) return;

		fprintf(file, ";.TITL 'Radial Image'\n");
		fprintf(file, ";.STITL 'Radial Image Editor, Copyright (c) Alexei Egorov aka FadeToBlack, 2008'\n");
		fprintf(file, ";.LSTOUT -\n");

		AnsiString s;
		for (int i=0; i<count; i++) {
			fprintf(file, "DB ");
			for (int j=0; j<lights; j++) {
				s = IntToStr(1 - data[i].getBit2(j));
				fprintf(file, s.c_str());
				if ((j + 1) % 8 == 0 && j != lights - 1) {
					fprintf(file, "b, ");
				}
			}
			fprintf(file, "b\n");
		}

		fprintf(file, ";.LSTOUT .\n");

		fclose(file);

	}

	void saveSBP(const AnsiString &name) {
		FILE *file = fopen(name.c_str(), "wb");
		if (!file) return;

        int magic = SBP_MAGIC;
        unsigned short lights_count = getLights();
        unsigned short sectors_count = getCount();
        unsigned char hole_size = getHole();

        // header
        fwrite(&magic, sizeof(magic), 1, file);
        fwrite(&lights_count, sizeof(lights_count), 1, file);
        fwrite(&sectors_count, sizeof(sectors_count), 1, file);
        fwrite(&hole, sizeof(hole_size), 1, file);

        
        for (int i=0; i<count; i++) {
        	fwrite(data[i].getData(), sizeof(unsigned char) * data[i].getSize(), 1, file);
        }
        
		fclose(file);

	}
    
	void loadSBP(const AnsiString &name) {

		FILE *file = fopen(name.c_str(), "rb");
		if (!file) return;

        int must_magic = SBP_MAGIC;
        int magic = 0;
        unsigned short lights_count = 0;
        unsigned short sectors_count = 0;
        unsigned char hole_size = 0;

        // header
        fread(&magic, sizeof(magic), 1, file);
        fread(&lights_count, sizeof(lights_count), 1, file);
        fread(&sectors_count, sizeof(sectors_count), 1, file);
        fread(&hole_size, sizeof(hole_size), 1, file);

        setSize(sectors_count, lights_count);
        setHole(hole_size);

        
        for (int i=0; i<count; i++) {
        	fread(data[i].getData(), sizeof(unsigned char) * data[i].getSize(), 1, file);
        }
        

		fclose(file);

	}
    

	void draw(TImage *image) {

		image->Canvas->Brush->Color = clBlack;
		image->Canvas->FillRect(image->Canvas->ClipRect);

		int cx = image->Canvas->ClipRect.Width();
		int cy = image->Canvas->ClipRect.Height();
		int cex = image->Canvas->ClipRect.Width() / 2;
		int cey = image->Canvas->ClipRect.Height() / 2;

		if (cx > cy) {
			cx = cy;
		} else {
			cy = cx;
		}

		float ratio = float(hole) / 100;
		image->Canvas->Brush->Color = clBlack;
		image->Canvas->Pen->Color = color;
		image->Canvas->Ellipse(cex - cx / 2, cey - cy /2, cex + cx / 2, cey + cy /2);
		image->Canvas->Ellipse(cex - cx / 2 * ratio, cey - cy / 2 * ratio, cex + cx / 2 * ratio, cey + cy / 2 * ratio);

		int sx = 2;
		int sy = 2;

		image->Canvas->Brush->Color = color;
		image->Canvas->Pen->Color = color;

		for (int j=0; j<lights; j++) {
			for (int i=0; i<count; i++) {
				float angle = 2 * M_PI / count * i - M_PI / 2;

				int x = cos(angle) * (cx * (j + 1) / lights / 2 * (1 - ratio) + cx / 2 * ratio) + cex;
				int y = sin(angle) * (cy * (j + 1) / lights / 2 * (1 - ratio) + cy / 2 * ratio) + cey;

				if (!data[i][j]) {
					continue;
				}

				image->Canvas->Ellipse(x - sx, y - sy, x + sx, y + sy);

			}
		}

		image->Canvas->Brush->Color = clBlack;
//		image->Canvas->Pen->Color = clBlue;
		image->Canvas->Font->Color = clWhite;

		AnsiString text = IntToStr(int(count)) + "x" + IntToStr(int(lights)) + " " + IntToStr(int(ratio * 100)) + "%";
		image->Canvas->TextOutA(10, 10 , text);

	}

	void negate() {
		for (int j=0; j<lights; j++) {
			for (int i=0; i<count; i++) {
				data[i].setBit(j, !data[i][j]);
			}
		}
	}

	TColor getColor() const {
		return color;
	}

	void setColor(TColor ncolor) {
		color = ncolor;
	}

};



#endif


