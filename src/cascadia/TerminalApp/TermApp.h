#pragma once

#include "TermApp.g.h"
#include <winrt/Microsoft.Terminal.TerminalConnection.h>
#include <winrt/Microsoft.Terminal.TerminalControl.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "Tab.h"
#include "CascadiaSettings.h"

namespace winrt::Microsoft::Terminal::TerminalApp::implementation
{
    struct TermApp : TermAppT<TermApp>
    {
        TermApp();

        Windows::UI::Xaml::UIElement GetRoot();
        void Create();

        ~TermApp();

        Windows::UI::Xaml::Markup::IXamlType GetXamlType(Windows::UI::Xaml::Interop::TypeName const& type);
        Windows::UI::Xaml::Markup::IXamlType GetXamlType(hstring const& fullName);
        com_array<Windows::UI::Xaml::Markup::XmlnsDefinition> GetXmlnsDefinitions();

    private:
        // Xaml interop: this list of providers will be queried to resolve types encountered
        // when loading .xaml and .xbf files.
        std::vector<Windows::UI::Xaml::Markup::IXamlMetadataProvider> _xamlMetadataProviders;

        Windows::UI::Xaml::Controls::Grid _root;
        Microsoft::UI::Xaml::Controls::TabView _tabView;
        Windows::UI::Xaml::Controls::Grid _tabContent;

        std::vector<std::shared_ptr<Tab>> _tabs;

        std::unique_ptr<::Microsoft::Terminal::TerminalApp::CascadiaSettings> _settings;

        void _Create();

        void _LoadSettings();


        void _UpdateTabView();

        void _CreateNewTabFromSettings(winrt::Microsoft::Terminal::Settings::TerminalSettings settings);

        void _DoNewTab(std::optional<int> profileIndex);
        void _DoCloseTab();
        void _SelectNextTab(const bool bMoveRight);
        void _FocusTabAtIndex(size_t tabIndex);
        int _GetFocusedTabIndex() const;

        void _DoScroll(int delta);
        // Todo: add more event implementations here
        // MSFT:20641985: Add keybindings for Next/Prev tab
        // MSFT:20641986: Add keybindings for New Window
    };
}

namespace winrt::Microsoft::Terminal::TerminalApp::factory_implementation
{
    struct TermApp : TermAppT<TermApp, implementation::TermApp>
    {
    };
}
