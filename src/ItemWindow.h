#pragma once
#include <common.h>

#include <shobjidl.h>
#include <atlbase.h>

namespace chromabrowse {

class ItemWindow;
class FolderWindow;

extern long numOpenWindows;
extern CComPtr<ItemWindow> activeWindow;

class ItemWindow : public IUnknown {
protected:
    // calculated in init()
    static int CAPTION_HEIGHT;

public:
    static void init();
    static void uninit();

    ItemWindow(CComPtr<ItemWindow> parent, CComPtr<IShellItem> item);
    virtual ~ItemWindow();

    bool create(RECT rect, int showCommand);
    void close();
    void activate();
    void setPos(POINT pos);
    void move(int x, int y);

    virtual bool handleTopLevelMessage(MSG *msg);

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID id, void **obj) override;
    STDMETHODIMP_(ULONG) AddRef() override;
    STDMETHODIMP_(ULONG) Release() override;

    CComPtr<IShellItem> item;

protected:
    static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT handleMessage(UINT message, WPARAM wParam, LPARAM lParam);

    virtual void onCreate();
    virtual void onDestroy();
    virtual void onActivate(WPARAM wParam);
    virtual void onSize(int width, int height);

    void openChild(CComPtr<IShellItem> childItem);
    void closeChild();
    virtual void onChildDetached();

    HWND hwnd;
    CComHeapPtr<wchar_t> title;

    CComPtr<ItemWindow> parent, child;

private:
    virtual const wchar_t * className() = 0;

    void windowRectChanged();
    // for DWM custom frame:
    void extendWindowFrame();
    LRESULT hitTestNCA(POINT cursor);
    void paintCustomCaption(HDC hdc);

    void openParent();
    void detachFromParent();
    POINT childPos(); // top left corner of child
    POINT parentPos(); // top right corner of parent
    CComPtr<IShellItem> resolveLink(CComPtr<IShellItem> linkItem);

    HICON iconLarge = nullptr, iconSmall = nullptr;

    HWND parentButton;

    POINT moveAccum;

    // IUnknown
    long refCount = 1;
};

} // namespace
