#pragma once
#include <common.h>

#include "ItemWindow.h"
#include <windows.h>

namespace chromabrowse {

class FolderWindow : public ItemWindow, public IServiceProvider, public ICommDlgBrowser {
public:
    static const int DEFAULT_WIDTH = 231; // just large enough for scrollbar tooltips
    static const int DEFAULT_HEIGHT = 450;

    static void init();

    FolderWindow(CComPtr<ItemWindow> parent, CComPtr<IShellItem> item);

    bool handleTopLevelMessage(MSG *msg) override;

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID id, void **obj) override;
    STDMETHODIMP_(ULONG) AddRef() override;
    STDMETHODIMP_(ULONG) Release() override;
    // IServiceProvider
    STDMETHODIMP QueryService(REFGUID guidService, REFIID riid, void **ppv) override;
    // ICommDlgBrowser
    STDMETHODIMP OnDefaultCommand(IShellView *view) override;
    STDMETHODIMP OnStateChange(IShellView *view, ULONG change) override;
    STDMETHODIMP IncludeObject(IShellView *view, PCUITEMID_CHILD pidl) override;

protected:
    LRESULT handleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;

    void onCreate() override;
    void onDestroy() override;
    void onActivate(WPARAM wParam) override;
    void onSize(int width, int height) override;

    void onChildDetached() override;

private:
    const wchar_t * className() override;

    void selectionChanged();
    void resultsFolderFallback();

    CComPtr<IExplorerBrowser> browser;
    CComPtr<IShellView> shellView;

    bool ignoreNextSelection = false;
};

} // namespace
