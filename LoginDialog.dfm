object LoginDiaglog: TLoginDiaglog
  Left = 0
  Top = 0
  Caption = 'Login'
  ClientHeight = 187
  ClientWidth = 238
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 59
    Width = 11
    Height = 15
    Caption = 'ID'
  end
  object Label2: TLabel
    Left = 24
    Top = 93
    Width = 50
    Height = 15
    Caption = 'Password'
  end
  object Label3: TLabel
    Left = 24
    Top = 24
    Width = 194
    Height = 15
    Alignment = taCenter
    Caption = 'Protected Flight Information'
  end
  object EditID: TEdit
    Left = 97
    Top = 56
    Width = 121
    Height = 23
    TabOrder = 0
  end
  object EditPassword: TEdit
    Left = 97
    Top = 90
    Width = 121
    Height = 23
    PasswordChar = '*'
    TabOrder = 1
  end
  object ButtonLogin: TButton
    Left = 24
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Login'
    Default = True
    TabOrder = 2
    OnClick = ButtonLoginClick
  end
  object ButtonCancel: TButton
    Left = 143
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = ButtonCancelClick
  end
end
