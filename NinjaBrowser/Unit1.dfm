object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'NinjaBrowser'
  ClientHeight = 774
  ClientWidth = 1033
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Fixedsys'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 16
  object PanelTopMain: TPanel
    Left = 0
    Top = 0
    Width = 1033
    Height = 36
    Align = alTop
    TabOrder = 0
    object PanelForward: TPanel
      Left = 37
      Top = 1
      Width = 36
      Height = 34
      Align = alLeft
      BevelOuter = bvNone
      Padding.Left = 4
      Padding.Top = 4
      Padding.Right = 4
      Padding.Bottom = 4
      TabOrder = 0
      object SpeedButtonGoForward: TSpeedButton
        Left = 4
        Top = 4
        Width = 28
        Height = 26
        Align = alClient
        Caption = '>'
        OnClick = SpeedButtonGoForwardClick
        ExplicitLeft = 1
        ExplicitTop = 7
        ExplicitWidth = 33
        ExplicitHeight = 27
      end
    end
    object PanelURL: TPanel
      Left = 73
      Top = 1
      Width = 738
      Height = 34
      Align = alClient
      BevelOuter = bvNone
      Padding.Left = 6
      Padding.Top = 6
      Padding.Right = 6
      Padding.Bottom = 6
      TabOrder = 1
      object EditURL: TEdit
        Left = 6
        Top = 6
        Width = 726
        Height = 22
        Align = alClient
        TabOrder = 0
        OnKeyDown = EditURLKeyDown
        OnKeyUp = EditURLKeyUp
        ExplicitHeight = 24
      end
    end
    object PanelGo: TPanel
      Left = 811
      Top = 1
      Width = 36
      Height = 34
      Align = alRight
      BevelOuter = bvNone
      Padding.Left = 4
      Padding.Top = 4
      Padding.Right = 4
      Padding.Bottom = 4
      TabOrder = 2
      object SpeedButtonGo: TSpeedButton
        Left = 4
        Top = 4
        Width = 28
        Height = 26
        Align = alClient
        Caption = 'Go'
        OnClick = SpeedButtonGoClick
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 10
        ExplicitHeight = 39
      end
    end
    object PanelBackward: TPanel
      Left = 1
      Top = 1
      Width = 36
      Height = 34
      Align = alLeft
      BevelOuter = bvNone
      Padding.Left = 4
      Padding.Top = 4
      Padding.Right = 4
      Padding.Bottom = 4
      TabOrder = 3
      object SpeedButtonGoBack: TSpeedButton
        Left = 4
        Top = 4
        Width = 28
        Height = 26
        Align = alClient
        Caption = '<'
        OnClick = SpeedButtonGoBackClick
        ExplicitTop = 7
        ExplicitWidth = 31
        ExplicitHeight = 27
      end
    end
    object PanelTab: TPanel
      Left = 847
      Top = 1
      Width = 185
      Height = 34
      Align = alRight
      BevelOuter = bvNone
      Padding.Left = 4
      Padding.Top = 4
      Padding.Right = 4
      Padding.Bottom = 4
      TabOrder = 4
      object ButtonFixMe: TButton
        Left = 4
        Top = 4
        Width = 177
        Height = 26
        Align = alClient
        Caption = 'Fix Me Help'
        TabOrder = 0
        OnClick = ButtonFixMeClick
      end
    end
  end
  object MemoDBG: TMemo
    Left = 0
    Top = 634
    Width = 1033
    Height = 121
    Align = alBottom
    Lines.Strings = (
      'MemoDBG')
    ScrollBars = ssBoth
    TabOrder = 1
    Visible = False
  end
  object PageControl2: TPageControl
    Left = 0
    Top = 36
    Width = 1033
    Height = 598
    ActivePage = TabSheet1
    Align = alClient
    DoubleBuffered = False
    ParentDoubleBuffered = False
    TabOrder = 2
    TabStop = False
    object TabSheet1: TTabSheet
      Caption = 'Browser'
      object PageControl1: TPageControl
        Left = 0
        Top = 0
        Width = 1025
        Height = 566
        Align = alClient
        DoubleBuffered = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        MultiLine = True
        ParentDoubleBuffered = False
        ParentFont = False
        TabOrder = 0
        TabPosition = tpBottom
        TabStop = False
        OnChange = PageControl1Change
      end
      object ButtonAddTabBrowser: TButton
        Left = 856
        Top = 0
        Width = 115
        Height = 25
        Caption = 'AddTabBrowser'
        TabOrder = 1
        Visible = False
        OnClick = ButtonAddTabBrowserClick
      end
      object ButtonCloseQuery: TButton
        Left = 969
        Top = 0
        Width = 52
        Height = 25
        Caption = 'close'
        TabOrder = 2
        Visible = False
        OnClick = ButtonCloseQueryClick
      end
      object ButtonExitBrowser: TButton
        Left = 750
        Top = 0
        Width = 106
        Height = 25
        Caption = 'ExitBrowser'
        TabOrder = 3
        Visible = False
        OnClick = ButtonExitBrowserClick
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 755
    Width = 1033
    Height = 19
    Panels = <
      item
        Text = 'Status'
        Width = 50
      end>
  end
end
