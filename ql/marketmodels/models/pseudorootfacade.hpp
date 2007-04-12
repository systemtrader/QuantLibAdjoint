/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007 Ferdinando Ametrano
 Copyright (C) 2007 Mark Joshi

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef quantlib_pseudoroot_facade_hpp
#define quantlib_pseudoroot_facade_hpp

#include <ql/marketmodels/marketmodel.hpp>
#include <ql/marketmodels/evolutiondescription.hpp>
#include <ql/math/matrix.hpp>
#include <vector>

namespace QuantLib
{
    class PseudoRootFacade : public MarketModel {
      public:
        PseudoRootFacade(
            const std::vector<Matrix>& covariancePseudoRoots,
            const std::vector<Rate>& rateTimes,
            const std::vector<Rate>& initialRates,
            const std::vector<Spread>& displacements);
        //! \name MarketModel interface
        //@{
        const std::vector<Rate>& initialRates() const;
        const std::vector<Spread>& displacements() const;
        const EvolutionDescription& evolution() const;
        Size numberOfRates() const;
        Size numberOfFactors() const;
        Size numberOfSteps() const; 
        const Matrix& pseudoRoot(Size i) const;
        //@}
      private:
        Size numberOfFactors_, numberOfRates_, numberOfSteps_;
        std::vector<Rate> initialRates_;
        std::vector<Spread> displacements_;
        EvolutionDescription evolution_;
        std::vector<Matrix> covariancePseudoRoots_;
    };

    // inline

    inline const std::vector<Rate>& PseudoRootFacade::initialRates() const {
        return initialRates_;
    }

    inline const std::vector<Spread>& PseudoRootFacade::displacements() const {
        return displacements_;
    }

    inline const EvolutionDescription& PseudoRootFacade::evolution() const {
        return evolution_;
    }

    inline Size PseudoRootFacade::numberOfRates() const {
        return numberOfRates_;
    }

    inline Size PseudoRootFacade::numberOfFactors() const {
        return numberOfFactors_;
    }

    inline Size PseudoRootFacade::numberOfSteps() const {
        return numberOfSteps_;
    }

    inline const Matrix& PseudoRootFacade::pseudoRoot(Size i) const {
        QL_REQUIRE(i<numberOfSteps_,
                   "the index " << i << " is invalid: it must be less than "
                   "number of steps (" << numberOfSteps_ << ")");
        return covariancePseudoRoots_[i];
    }
}

#endif