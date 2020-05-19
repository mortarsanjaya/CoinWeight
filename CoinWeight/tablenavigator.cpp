//
//  tablenavigator.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-10.
//  Copyright © 2020 -. All rights reserved.
//

#include "tablenavigator.hpp"

//************************** Constructor
TableNavigator::TableNavigator(const size_t nEntries,
                               const size_t nRowsDisplay,
                               const size_t nColumns) :
nEntries(nEntries), nRowsDisplay(nRowsDisplay), nColumns(nColumns),
    topRowDisplay(0), currentRowActual(0), currentRowDisplay(0),
    currentColumn(0) {}



//************************** Field accessors
const size_t TableNavigator::numOfEntries() const {
    return nEntries;
}

const size_t TableNavigator::numOfRowsDisplayed() const {
    return nRowsDisplay;
}

const size_t TableNavigator::numOfColumns() const {
    return nColumns;
}

const size_t TableNavigator::currTopRow() const {
    return topRowDisplay;
}

const size_t TableNavigator::currRowActual() const {
    return currentRowActual;
}

const size_t TableNavigator::currRowDisplay() const {
    return currentRowDisplay;
}

const size_t TableNavigator::currColumn() const {
    return currentColumn;
}

const size_t TableNavigator::currIndex() const {
    return (nColumns * currentRowActual + currentColumn);
}



//************************** Table scroll functions
void TableNavigator::scrollUp() {
    if (currentRowActual > 0) {
        --currentRowActual;
        if (currentRowDisplay == 0) {
            --topRowDisplay;
        } else {
            --currentRowDisplay;
        }
    }
}

void TableNavigator::scrollDown() {
    if (currIndex() + nColumns < nEntries) {
        ++currentRowActual;
        if (currentRowDisplay == nRowsDisplay - 1) {
            ++topRowDisplay;
        } else {
            ++currentRowDisplay;
        }
    }
}

void TableNavigator::scrollLeft() {
    if (currentColumn > 0) {
        --currentColumn;
    }
}

void TableNavigator::scrollRight() {
    if ((currIndex() + 1 < nEntries) && (currentColumn + 1 < nColumns)) {
        ++currentColumn;
    }
}

void TableNavigator::reset() {
    topRowDisplay = 0;
    currentRowActual = 0;
    currentRowDisplay = 0;
    currentColumn = 0;
}
