//
// ********************************************************************
// *                                                                  *
// * Copyright 2022 The TOPAS Collaboration                           *
// *                                                                  *
// * Permission is hereby granted, free of charge, to any person      *
// * obtaining a copy of this software and associated documentation   *
// * files (the "Software"), to deal in the Software without          *
// * restriction, including without limitation the rights to use,     *
// * copy, modify, merge, publish, distribute, sublicense, and/or     *
// * sell copies of the Software, and to permit persons to whom the   *
// * Software is furnished to do so, subject to the following         *
// * conditions:                                                      *
// *                                                                  *
// * The above copyright notice and this permission notice shall be   *
// * included in all copies or substantial portions of the Software.  *
// *                                                                  *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,  *
// * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES  *
// * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND         *
// * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT      *
// * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,     *
// * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
// * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    *
// * OTHER DEALINGS IN THE SOFTWARE.                                  *
// *                                                                  *
// ********************************************************************
//

#include "TsDoubleFromDoubleMinusValue.hh"

TsDoubleFromDoubleMinusValue::TsDoubleFromDoubleMinusValue(TsParameterManager* pM, TsParameterFile* pf, TsTempParameter* tempParameter,
														 const G4String& nameOfOtherParameter, const G4String& value, const G4String& unit)
:TsVParameter(pM, pf, tempParameter), fUnit(unit)
{
	QuitIfMustBeAbsolute();

	CheckUnit(unit);

	fValue = ConvertToDouble(value);

	fNameOfOtherParameter = ParseNameOfOtherParameter(nameOfOtherParameter, "d");
}


TsDoubleFromDoubleMinusValue::~TsDoubleFromDoubleMinusValue()
{
}


void TsDoubleFromDoubleMinusValue::CheckRelativeParameterConsistency()
{
	CheckUnitAgreement(fNameOfOtherParameter);
}


G4String TsDoubleFromDoubleMinusValue::GetType()
{
	G4String type = "d";
	return type;
}


G4String TsDoubleFromDoubleMinusValue::GetUnit()
{
	return fUnit;
}


G4double TsDoubleFromDoubleMinusValue::GetDoubleValue()
{
	fUsed = true;
	return EvaluateDoubleParameter(fNameOfOtherParameter) - fValue * fPm->GetUnitValue(fUnit);
}


G4String TsDoubleFromDoubleMinusValue::GetHTMLValue()
{
	G4String output;
	output += EvaluateAsHTML(fNameOfOtherParameter);
	output += " - ";
	output += G4UIcommand::ConvertToString(fValue);
	output += " ";
	output += fUnit;
	return output;
}