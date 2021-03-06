/**
 * @file QR.h
 * @author  David Millan <david.millan@damiles.com>
 * @version 0.1
 *
 * @section LICENSE
 *
 * Copyright © 2011, Augmate Corporation LLC.
 * This file is part of VERSE.
 * 
 * VERSE is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * VERSE is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with VERSE. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * QR decode images.
 */
#ifndef AR_QR_h
#define AR_QR_h

#include <Core/EventDispatcher.h>
#include <Events/QREvent.h>

#include <cv.h>
#include <highgui.h>

#include <libdecodeqr/decodeqr.h>

namespace AR{

class QR: public Core::EventDispatcher {
public:
	QR();
	void process(IplImage* img);

private:
	QrDecoderHandle decoder;
	unsigned char* text;
	int text_size;
	IplImage *src;
	int START;
};


}
#endif
