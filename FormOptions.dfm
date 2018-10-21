object Form2: TForm2
  Left = 372
  Top = 321
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 274
  ClientWidth = 208
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 193
    Height = 81
    Caption = 'Size'
    TabOrder = 0
    object Label1: TLabel
      Left = 20
      Top = 19
      Width = 28
      Height = 13
      Alignment = taRightJustify
      Caption = 'Ligths'
    end
    object Label2: TLabel
      Left = 12
      Top = 43
      Width = 36
      Height = 13
      Alignment = taRightJustify
      Caption = 'Sectors'
    end
    object seLights: TCSpinEdit
      Left = 56
      Top = 16
      Width = 97
      Height = 22
      EditorEnabled = False
      Increment = 8
      MaxValue = 128
      MinValue = 8
      TabOrder = 0
      Value = 32
    end
    object seSectors: TCSpinEdit
      Left = 56
      Top = 40
      Width = 97
      Height = 22
      EditorEnabled = False
      Increment = 64
      MaxValue = 1024
      MinValue = 128
      TabOrder = 1
      Value = 256
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 96
    Width = 193
    Height = 73
    Caption = 'Hole'
    TabOrder = 1
    object Label3: TLabel
      Left = 28
      Top = 27
      Width = 20
      Height = 13
      Alignment = taRightJustify
      Caption = 'Size'
    end
    object Label4: TLabel
      Left = 160
      Top = 27
      Width = 8
      Height = 13
      Alignment = taRightJustify
      Caption = '%'
    end
    object seHole: TCSpinEdit
      Left = 56
      Top = 24
      Width = 97
      Height = 22
      EditorEnabled = False
      MaxValue = 100
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 128
    Top = 240
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
  object BitBtn2: TBitBtn
    Left = 8
    Top = 240
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 176
    Width = 89
    Height = 49
    Caption = 'Edit'
    TabOrder = 4
    object cbEditEnable: TCheckBox
      Left = 8
      Top = 24
      Width = 57
      Height = 17
      Caption = 'Enable'
      TabOrder = 0
    end
  end
  object GroupBox4: TGroupBox
    Left = 104
    Top = 176
    Width = 97
    Height = 49
    Caption = 'Color'
    TabOrder = 5
    object shColor: TShape
      Left = 16
      Top = 16
      Width = 65
      Height = 25
      Brush.Color = clBlue
      OnMouseDown = shColorMouseDown
    end
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 88
    Top = 240
  end
end
