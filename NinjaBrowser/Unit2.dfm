object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Fix Me'
  ClientHeight = 501
  ClientWidth = 546
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PanelFixMe: TPanel
    Left = 0
    Top = 0
    Width = 546
    Height = 460
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 0
    ExplicitHeight = 437
    object MemoFixMe: TMemo
      Left = 10
      Top = 10
      Width = 526
      Height = 440
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Fixedsys'
      Font.Style = []
      Lines.Strings = (
        'MemoFixMe')
      ParentFont = False
      TabOrder = 0
      ExplicitHeight = 417
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 460
    Width = 546
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 437
    object ButtonClose: TButton
      Left = 0
      Top = 0
      Width = 546
      Height = 41
      Align = alClient
      Caption = 'YES'
      TabOrder = 0
      OnClick = ButtonCloseClick
    end
  end
end
