/*
 ==============================================================================
 
 OscValueTreeItem.cpp
 Created: 12 Oct 2017 1:53:46am
 Author:  Jefferson Bledsoe
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "OscValueTreeItem.h"

//==============================================================================
OscValueTreeItem::OscValueTreeItem (const ValueTree& v)
: tree (v)
{
    tree.addListener (this);
}

String OscValueTreeItem::getUniqueName() const
{
    return tree["name"].toString();
}

bool OscValueTreeItem::mightContainSubItems()
{
    return tree.getNumChildren() > 0;
}

void OscValueTreeItem::paintItem (Graphics& g, int width, int height)
{
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawText (tree["name"].toString(),
                4, 0, width - 4, height,
                Justification::centredLeft, true);
}

void OscValueTreeItem::itemOpennessChanged (bool isNowOpen)
{
    if (isNowOpen && getNumSubItems() == 0)
        refreshSubItems();
    else
        clearSubItems();
}