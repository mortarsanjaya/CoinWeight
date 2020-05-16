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
    topRowDisplay(0), currentRow(0), currentColumn(0) {}



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

const size_t TableNavigator::currRow() const {
    return currentRow;
}

const size_t TableNavigator::currColumn() const {
    return currentColumn;
}

const size_t TableNavigator::currIndex() const {
    return (nColumns * currentRow + currentColumn);
}



//************************** Table scroll functions
void TableNavigator::scrollUp() {
    if (currentRow > 0) {
        --currentRow;
        if (topRowDisplay > currentRow) {
            topRowDisplay = currentRow;
        }
    }
}

void TableNavigator::scrollDown() {
    if (currIndex() + nColumns < nEntries) {
        ++currentRow;
        if (topRowDisplay + nRowsDisplay <= currentRow) {
            topRowDisplay = currentRow - nRowsDisplay;
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
    currentRow = 0;
    currentColumn = 0;
}
