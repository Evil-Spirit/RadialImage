object Form3: TForm3
  Left = 371
  Top = 302
  BorderStyle = bsDialog
  Caption = 'Turn'
  ClientHeight = 158
  ClientWidth = 215
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn2: TBitBtn
    Left = 8
    Top = 128
    Width = 75
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
  object BitBtn1: TBitBtn
    Left = 128
    Top = 128
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkCancel
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 201
    Height = 49
    Caption = 'Sectors'
    TabOrder = 2
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 185
      Height = 21
      TabOrder = 0
      Text = '0'
      OnChange = Edit1Change
    end
  end
  object GroupBox2: TGroupBox
    Left = 6
    Top = 64
    Width = 201
    Height = 49
    Caption = 'Angle'
    TabOrder = 3
    object Edit2: TEdit
      Left = 8
      Top = 16
      Width = 185
      Height = 21
      TabOrder = 0
      Text = '0'
      OnChange = Edit2Change
    end
  end
end
