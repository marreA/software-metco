/*   Copyright 2013 Juan Rada-Vilela

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/*
 * FclExporter.cpp
 *
 *  Created on: 8/12/2012
 *      Author: jcrada
 */

#include "fl/imex/FclExporter.h"

#include "fl/Headers.h"

#include <sstream>

namespace fl {

    FclExporter::FclExporter() { }

    FclExporter::~FclExporter() { }

    std::string FclExporter::name() const {
        return "FclExporter";
    }

    std::string FclExporter::toString(const Engine* engine) const {
        std::ostringstream fcl;
        fcl << "FUNCTION_BLOCK " << engine->getName() << "\n\n";

        fcl << "VAR_INPUT\n";
        for (int i = 0; i < engine->numberOfInputVariables(); ++i) {
            fcl << engine->getInputVariable(i)->getName() << ": REAL;"
                    << "\n";
        }
        fcl << "END_VAR\n\n";

        fcl << "VAR_OUTPUT\n";
        for (int i = 0; i < engine->numberOfOutputVariables(); ++i) {
            fcl << engine->getOutputVariable(i)->getName() << ": REAL;"
                    << "\n";
        }
        fcl << "END_VAR\n\n";

        for (int i = 0; i < engine->numberOfInputVariables(); ++i) {
            InputVariable* inputVariable = engine->getInputVariable(i);
            fcl << "FUZZIFY " << inputVariable->getName() << "\n";
            fcl << "RANGE := (" << fl::Op::str(2, " .. ",
                    inputVariable->getMinimum(), inputVariable->getMaximum())
                    << ");\n";

            for (int t = 0; t < inputVariable->numberOfTerms(); ++t) {
                Term* term = inputVariable->getTerm(t);
                fcl << "TERM " << term->getName() << " := " << toFcl(term)
                        << ";\n";
            }
            fcl << "END_FUZZIFY\n\n";
        }

        for (int i = 0; i < engine->numberOfOutputVariables(); ++i) {
            OutputVariable* outputVariable = engine->getOutputVariable(i);
            fcl << "DEFUZZIFY " << outputVariable->getName() << "\n";
            fcl << "RANGE := (" << fl::Op::str(2, " .. ",
                    outputVariable->getMinimum(), outputVariable->getMaximum())
                    << ");\n";

            for (int t = 0; t < outputVariable->numberOfTerms(); ++t) {
                Term* term = outputVariable->getTerm(t);
                fcl << "TERM " << term->getName() << " := " << toFcl(term)
                        << ";\n";
            }
            fcl << "\n";

            fcl << "METHOD : " << toFcl(outputVariable->getDefuzzifier()) << ";"
                    << "\n";

            if (outputVariable->output()->getAccumulation())
                fcl << "ACCU : " << toFcl(outputVariable->output()->getAccumulation())
                << ";\n";

            fcl << "DEFAULT := " << fl::Op::str(outputVariable->getDefaultValue());
            if (outputVariable->isLockingValidOutput()) {
                fcl << " | NC";
            }
            fcl << ";\n";

            if (outputVariable->isLockingValidOutput() or outputVariable->isLockingOutputRange()) {
                fcl << "LOCK : ";
                std::string lock;
                if (outputVariable->isLockingValidOutput()) {
                    lock = "VALID";
                }
                if (outputVariable->isLockingOutputRange()) {
                    if (not lock.empty()) lock += " | ";
                    lock += "RANGE";
                }
                fcl << lock << ";\n";
            }

            fcl << "END_DEFUZZIFY\n";
            fcl << "\n";
        }

        for (int i = 0; i < engine->numberOfRuleBlocks(); ++i) {
            RuleBlock* ruleblock = engine->getRuleBlock(i);
            fcl << "RULEBLOCK " << ruleblock->getName() << "\n";

            if (ruleblock->getTnorm())
                fcl << "AND : " << toFcl(ruleblock->getTnorm()) << ";\n";
            if (ruleblock->getSnorm())
                fcl << "OR : " << toFcl(ruleblock->getSnorm()) << ";\n";
            if (ruleblock->getActivation())
                fcl << "ACT : " << toFcl(ruleblock->getActivation()) << ";\n";

            fcl << "\n";

            for (int r = 0; r < ruleblock->numberOfRules(); ++r) {
                fcl << "RULE " << (r + 1) << " : " <<
                        ruleblock->getRule(r)->getUnparsedRule() << "\n";
            }
            fcl << "END_RULEBLOCK\n";
            fcl << "\n";
        }

        fcl << "END_FUNCTION_BLOCK";
        return fcl.str();
    }

    std::string FclExporter::toFcl(const TNorm * tnorm) const {
        if (not tnorm) return "";
        std::string name = tnorm->className();
        if (name == Minimum().className()) return "MIN";
        if (name == AlgebraicProduct().className()) return "PROD";
        if (name == BoundedDifference().className()) return "BDIF";
        if (name == DrasticProduct().className()) return "DPROD";
        if (name == EinsteinProduct().className()) return "EPROD";
        if (name == HamacherProduct().className()) return "HPROD";
        return tnorm->className();
    }

    std::string FclExporter::toFcl(const SNorm * snorm) const {
        if (not snorm) return "";
        std::string name = snorm->className();
        if (name == Maximum().className()) return "MAX";
        if (name == AlgebraicSum().className()) return "ASUM";
        if (name == NormalizedSum().className()) return "NSUM";
        if (name == BoundedSum().className()) return "BSUM";
        if (name == DrasticSum().className()) return "DSUM";
        if (name == EinsteinSum().className()) return "ESUM";
        if (name == HamacherSum().className()) return "HSUM";
        return snorm->className();
    }

    std::string FclExporter::toFcl(const Defuzzifier* defuzzifier) const {
        if (not defuzzifier) return "";
        if (defuzzifier->className() == Centroid().className()) return "COG";
        if (defuzzifier->className() == Bisector().className()) return "COA";
        if (defuzzifier->className() == SmallestOfMaximum().className()) return "LM";
        if (defuzzifier->className() == LargestOfMaximum().className()) return "RM";
        if (defuzzifier->className() == MeanOfMaximum().className()) return "MM";
        if (defuzzifier->className() == WeightedAverage().className()) return "COGS";
        if (defuzzifier->className() == WeightedSum().className()) return "COGSS";
        return defuzzifier->className();
    }

    std::string FclExporter::toFcl(const Term* term) const {
        if (term->className() == Discrete().className()) {
            const Discrete* discrete = dynamic_cast<const Discrete*> (term);
            std::ostringstream ss;
            for (std::size_t i = 0; i < discrete->x.size(); ++i) {
                ss << "(" << fl::Op::str(discrete->x.at(i)) << ", "
                        << fl::Op::str(discrete->y.at(i)) << ")";
                if (i < discrete->x.size() - 1) ss << " ";
            }
            return ss.str();
        }

        if (term->className() == Constant().className()) {
            const Constant* constant = dynamic_cast<const Constant*> (term);
            return fl::Op::str(constant->getValue());
        }

        return term->toString();
    }

}
