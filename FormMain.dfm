object Form1: TForm1
  Left = 484
  Top = 110
  Width = 496
  Height = 480
  Caption = 'Radial'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Image2: TImage
    Left = 0
    Top = 0
    Width = 488
    Height = 434
    Align = alClient
    Stretch = True
    Visible = False
  end
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 488
    Height = 434
    Align = alClient
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 16
    object N1: TMenuItem
      Caption = 'File'
      object N2: TMenuItem
        Caption = 'Open...'
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = 'Save as...'
        OnClick = N3Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object Clear1: TMenuItem
        Caption = 'Clear'
        OnClick = Clear1Click
      end
      object Options1: TMenuItem
        Caption = 'Options'
        OnClick = Options1Click
      end
      object Negative1: TMenuItem
        Caption = 'Negative'
        OnClick = Negative1Click
      end
      object Turn1: TMenuItem
        Caption = 'Turn'
        OnClick = Turn1Click
      end
    end
    object N4: TMenuItem
      Caption = 'Help'
      object N5: TMenuItem
        Caption = 'About...'
        OnClick = N5Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'BMP|*.bmp|BSP_OLD|*.bsp_old|BSP|*.bsp|SBP|*.sbp'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 40
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.bsp'
    Filter = 'BSP|*.bsp|BSP_OLD|*.bsp_old|SBP|*.sbp'
    Left = 40
    Top = 48
  end
end
