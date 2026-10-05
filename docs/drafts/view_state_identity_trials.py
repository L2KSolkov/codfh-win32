from pathlib import Path

src = Path('src/recovered/unit_1A8B20.cpp').read_text()
a = src.index('void type_4F7EB8::sub_1AB440(')
z = src.index('\n}\n', a) + 3
old = src[a:z]
body = Path('docs/drafts/view_state_followup.cpp').read_text()
body = body[body.index('void type_4F7EB8::sub_1AB440('):]
x = 'dword_4FB9E0.unk_08.unk_2C'
forms = {
    'base': x,
    'pluszero': x + ' + 0.0f',
    'minuszero': x + ' - 0.0f',
    'plusnegativezero': x + ' + -0.0f',
    'minusnegativezero': x + ' - -0.0f',
    'zeroplus': '0.0f + ' + x,
    'negativezeroplus': '-0.0f + ' + x,
    'multiplyone': x + ' * 1.0f',
    'onemultiply': '1.0f * ' + x,
    'divideone': x + ' / 1.0f',
    'doublepluszero': x + ' + 0.0',
    'doubleminuszero': x + ' - 0.0',
    'minusplusone': '(' + x + ' - 1.0f) + 1.0f',
    'doubleminusplusone': '(' + x + ' - 1.0) + 1.0',
    'timesnegativenegative': '-(' + x + ' * -1.0f)',
    'dividebynegative': '-(' + x + ' / -1.0f)',
    'doubletwice': '(RwReal)(RwDouble)(RwReal)(RwDouble)' + x,
    'longdouble': '(long double)' + x,
    'longdoublecast': '(RwReal)(long double)' + x,
}
VS = {'vsi_' + n: [(old, body.replace(x, form))] for n, form in forms.items()}
