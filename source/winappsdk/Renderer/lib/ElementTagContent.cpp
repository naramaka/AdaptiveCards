// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ElementTagContent.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    ElementTagContent::ElementTagContent(rtom::IAdaptiveCardElement const& cardElement,
                                         rtxaml::Controls::Panel const& parentPanel,
                                         rtxaml::UIElement const& separator,
                                         rtxaml::Controls::ColumnDefinition const& columnDefinition,
                                         boolean expectedVisibility,
                                         boolean isStretchable)
    {
        m_cardElement = cardElement;
        m_parentPanel = parentPanel;
        m_separator = separator;
        m_columnDefinition = columnDefinition;
        ExpectedVisibility = expectedVisibility;
        IsStretchable = isStretchable;
    }

}