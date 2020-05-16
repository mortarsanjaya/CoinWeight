//
//  tablenavigator.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-10.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef tablenavigator_hpp
#define tablenavigator_hpp

#include <utility>

class TableNavigator final {
public:
    TableNavigator(const size_t nEntries,
                   const size_t nRowsDisplay,
                   const size_t nColumns);
    
    const size_t numOfEntries() const;
    const size_t numOfRowsDisplayed() const;
    const size_t numOfColumns() const;
    const size_t currTopRow() const;
    const size_t currRow() const;
    const size_t currColumn() const;
    const size_t currIndex() const;
    
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
    
    void reset();
    
private:
    const size_t nEntries;
    const size_t nRowsDisplay;
    const size_t nColumns;
    
    size_t topRowDisplay;
    size_t currentRow;
    size_t currentColumn;
};

#endif
