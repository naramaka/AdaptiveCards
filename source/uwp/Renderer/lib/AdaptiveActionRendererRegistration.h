// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionRendererRegistration.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveActionRendererRegistration : AdaptiveActionRendererRegistrationT<AdaptiveActionRendererRegistration>
    {
        using RegistrationMap =
            std::unordered_map<winrt::hstring, winrt::IAdaptiveActionRenderer, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

        AdaptiveActionRendererRegistration() = default;

        Uwp::IAdaptiveActionRenderer Get(winrt::hstring const& type);
        void Set(winrt::hstring const& type, winrt::IAdaptiveActionRenderer const& renderer);
        void Remove(winrt::hstring const& type);

        RegistrationMap m_registration;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveActionRendererRegistration
        : AdaptiveActionRendererRegistrationT<AdaptiveActionRendererRegistration, implementation::AdaptiveActionRendererRegistration>
    {
    };
}
