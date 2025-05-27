object LoginDiaglog: TLoginDiaglog
  Left = 0
  Top = 0
  Caption = 'Login'
  ClientHeight = 169
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
    Top = 35
    Width = 33
    Height = 15
    Caption = 'ID'
  end
  object Label2: TLabel
    Left = 24
    Top = 69
    Width = 50
    Height = 15
    Caption = 'Password'
  end
  object EditID: TEdit
    Left = 97
    Top = 32
    Width = 121
    Height = 23
    TabOrder = 0
  end
  object EditPassword: TEdit
    Left = 97
    Top = 66
    Width = 121
    Height = 23
    PasswordChar = '*'
    TabOrder = 1
  end
  object ButtonLogin: TButton
    Left = 24
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Login'
    TabOrder = 2
    OnClick = ButtonLoginClick
  end
  object ButtonCancel: TButton
    Left = 143
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
  end
end
