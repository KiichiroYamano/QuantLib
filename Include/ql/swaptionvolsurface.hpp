
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 * The license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.sourceforge.net/Authors.txt
*/

/*
    $Id$
    $Source$
    $Log$
    Revision 1.2  2001/05/14 17:09:47  lballabio
    Went for simplicity and removed Observer-Observable relationships from Instrument

    Revision 1.1  2001/04/09 14:03:54  nando
    all the *.hpp moved below the Include/ql level

    Revision 1.3  2001/04/06 18:46:19  nando
    changed Authors, Contributors, Licence and copyright header

*/

/*! \file swaptionvolsurface.hpp
    \brief Swaption volatility surface
*/

#ifndef quantlib_swaption_volatility_surface_h
#define quantlib_swaption_volatility_surface_h

#include "ql/qldefines.hpp"
#include "ql/date.hpp"
#include "ql/rate.hpp"
#include "ql/spread.hpp"
#include "ql/handle.hpp"
#include "ql/spread.hpp"

namespace QuantLib {

    //! Swaption volatility surface
    /*! This class is purely abstract and defines the interface of concrete
        swaption volatility structures which will be derived from this one.
    */
    class SwaptionVolatilitySurface {
      public:
        virtual ~SwaptionVolatilitySurface() {}
        //! returns the volatility for a given starting date and length
        virtual Rate vol(const Date& start, Time length) const = 0;
    };

    //! Swaption volatility surface with an added spread
    /*! This surface will remain linked to the original surface, i.e., any changes
        in the latter will be reflected in this surface as well.
    */
    class SpreadedSwaptionVolatilitySurface : public SwaptionVolatilitySurface {
      public:
        SpreadedSwaptionVolatilitySurface(
            const Handle<SwaptionVolatilitySurface>&, Spread spread);
        //! returns the volatility of the original surface plus the given spread
        Rate vol(const Date& start, Time length) const;
      private:
        Handle<SwaptionVolatilitySurface> theOriginalSurface;
        Spread theSpread;
    };


    // inline definitions

    inline SpreadedSwaptionVolatilitySurface::SpreadedSwaptionVolatilitySurface(
        const Handle<SwaptionVolatilitySurface>& h, Spread spread)
    : theOriginalSurface(h), theSpread(spread) {}

    inline Rate SpreadedSwaptionVolatilitySurface::vol(const Date& start,
        Time length) const {
            return theOriginalSurface->vol(start,length)+theSpread;
    }

}


#endif
