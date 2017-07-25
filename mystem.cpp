
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mystem.h"
#include "ext/mbstring/mbstring.h"
#include "mystem_iface.h"

#include <unicode/unistr.h>

#define MYSTEM_NS "Mystem"
#define MYSTEM_GRAM_CONST(NAME, VALUE) REGISTER_NS_LONG_CONSTANT(MYSTEM_NS "\\" "GramInfo",     NAME, VALUE, CONST_CS | CONST_PERSISTENT);
#define MYSTEM_QUAL_CONST(NAME, VALUE) REGISTER_NS_LONG_CONSTANT(MYSTEM_NS "\\" "QualityFlags", NAME, VALUE, CONST_CS | CONST_PERSISTENT);

inline TSymbol* UnicodeToSymbols(const UnicodeString & str)
{
    TSymbol* symbols;
    symbols = (TSymbol *)safe_emalloc(str.length(), sizeof(TSymbol), 0);
    for (int i = 0; i < str.length(); i++) {
        symbols[i] = static_cast<TSymbol>(str[i]);
    }
    return symbols;
}

inline zval* SymbolsToZval(const TSymbol* symbols, int len)
{
    std::string str;
    UnicodeString(symbols, len).toUTF8String(str);
    zend_string *zstr = zend_string_init((char *)str.c_str(), str.length(), 0);
    zval *res = (zval *)safe_emalloc(1, sizeof(zval), 0);
    ZVAL_STR(res, zstr);
    return res;
}

inline zval* LongToZval(int num)
{
    zval *res = (zval *)safe_emalloc(1, sizeof(zval), 0);
    ZVAL_LONG(res, num);
    return res;
}

const char* GramName(zend_long gram)
{
    /**
     * https://github.com/yandex/tomita-parser/blob/d951391916f2894f49e13d447be1dee707504e2c/src/library/lemmer/dictlib/yx_gram_enum.h
     */
    switch (gram) {
        case 126: return "Before";
        case 127: return "Postposition";  // POSTP
        case 128: return "Adjective";     // A      // Nomenus
        case 129: return "Adverb";        // ADV
        case 130: return "Composite";     // COM(P)
        case 131: return "Conjunction";   // CONJ
        case 132: return "Interjunction"; // INTJ
        case 133: return "Numeral";       // NUM
        case 134: return "Particle";      // PCL
        case 135: return "Preposition";   // PRE(P)
        case 136: return "Substantive";   // S
        case 137: return "Verb";          // V
        case 138: return "AdjNumeral";    // ANUM
        case 139: return "AdjPronoun";    // APRO
        case 140: return "AdvPronoun";    // ADVPRO
        case 141: return "SubstPronoun";  // SPRO
        case 142: return "Article";       // артикли
        case 143: return "PartOfIdiom";   // части идиом (прежде всего иностр. слов)
        case 144: return "Reserved";      // зарезервировано    // особые пометы
        case 145: return "Abbreviation";  // сокращения
        case 146: return "IrregularStem"; // чередование в корне (или супплетивизм)
        case 147: return "Informal";      // разговорная форма
        case 148: return "Distort";       // искаженная форма
        case 149: return "Contracted";    // стяжённая форма (фр. q' и т.п.)
        case 150: return "Obscene";       // обсц
        case 151: return "Rare";          // редк
        case 152: return "Awkward";       // затр
        case 153: return "Obsolete";      // устар
        case 154: return "SubstAdjective";// адъект
        case 155: return "FirstName";     // имя
        case 156: return "Surname";       // фам
        case 157: return "Patr";          // отч
        case 158: return "Geo";           // гео
        case 159: return "Proper";        // собств
        case 160: return "Present";       // наст  // Tempus
        case 161: return "Notpast";       // непрош
        case 162: return "Past";          // прош
        case 163: return "Future";        // буд. время (фр., ит.)
        case 164: return "Past2";         // фр. passe simple, ит. passato remoto
        case 165: return "Nominative";    // им    // Casus
        case 166: return "Genitive";      // род
        case 167: return "Dative";        // дат
        case 168: return "Accusative";    // вин
        case 169: return "Instrumental";  // твор
        case 170: return "Ablative";      // пр
        case 171: return "Partitive";     // парт(вин2)
        case 172: return "Locative";      // местн(пр2)
        case 173: return "Vocative";      // звательный
        case 174: return "Singular";      // ед    // Numerus
        case 175: return "Plural";        // мн
        case 176: return "Gerund";        // деепр // Modus
        case 177: return "Infinitive";    // инф
        case 178: return "Participle";    // прич
        case 179: return "Indicative";    // изъяв
        case 180: return "Imperative";    // пов
        case 181: return "Conditional";   // усл. наклонение (фр., ит.)
        case 182: return "Subjunctive";   // сослаг. накл. (фр., ит.)
        case 183: return "Short";         // кр    // Gradus
        case 184: return "Full";          // полн
        case 185: return "Superlative";   // прев
        case 186: return "Comparative";   // срав
        case 187: return "Possessive";    // притяж
        case 188: return "Person1";       // 1-л   // Personae
        case 189: return "Person2";       // 2-л
        case 190: return "Person3";       // 3-л
        case 191: return "Feminine";      // жен   // Gender (genus)
        case 192: return "Masculine";     // муж
        case 193: return "Neuter";        // сред
        case 194: return "MasFem";        // мж
        case 195: return "Perfect";       // сов   // Perfectum-imperfectum (Accept)
        case 196: return "Imperfect";     // несов
        case 197: return "Passive";       // страд // Voice (Genus)
        case 198: return "Active";        // действ
        case 199: return "Reflexive";     // возвратные
        case 200: return "Impersonal";    // безличные
        case 201: return "Animated";      // од    // Animated
        case 202: return "Inanimated";    // неод
        case 203: return "Praedic";       // прдк
        case 204: return "Parenth";       // вводн
        case 205: return "Transitive";    // пе     //transitivity
        case 206: return "Intransitive";  // нп
        case 207: return "Definite";      // опред. члены   //definiteness
        case 208: return "Indefinite";    // неопред. члены
        case 209: return "SimConj";       // сочинит. (для союзов)
        case 210: return "SubConj";       // подчинит. (для союзов)
        case 211: return "PronounConj";   // местоимение-союз ("я знаю, _что_ вы сделали прошлым летом")
        case 212: return "CorrelateConj"; // вторая зависимая часть парных союзов - "если ... _то_ ... ", "как ... _так_ и ..."
        case 213: return "AuxVerb";       //вспомогательный глагол в аналитической форме ("_будем_ думать")
        case 214: return "Dual";
        case 215: return "Poss1p";
        case 216: return "Poss1pSg";
        case 217: return "Poss1pPl";
        case 218: return "Poss2p";
        case 219: return "Poss2pSg";
        case 220: return "Poss2pPl";
        case 221: return "Poss3p";
        case 222: return "Poss3pSg";
        case 223: return "Poss3pPl";
        case 224: return "Predic1pSg";
        case 225: return "Predic1pPl";
        case 226: return "Predic2pSg";
        case 227: return "Predic2pPl";
        case 228: return "Predic3pSg";
        case 229: return "Predic3pPl";
        case 230: return "Elative";
        case 231: return "DerivedAdjective";
        case 232: return "Evidential";
        case 233: return "Negated";
        case 234: return "Potential";
        case 235: return "Medial";
        case 236: return "Human";
        case 237: return "AssocPlural";
        case 238: return "Optative";
        case 239: return "Converb";
        case 240: return "Simultaneous";
        case 241: return "Connegative";
        case 242: return "Resultative";
        case 243: return "Subjective";
        case 244: return "Count"; // счётная форма
        case 245: return "GoodForm";
        case 246: return "PredicPoss";
        case 247: return "Intention";
        case 248: return "Honorific";
        case 249: return "Equative";
        case 250: return "Predic";
        case 251: return "Obligatory";
        case 252: return "Max";
        default:  return "Invalid";
    }
}

inline zval* GramInfoToZval(const char* info, int asString)
{
    zval *res = (zval *)safe_emalloc(1, sizeof(zval), 0);
    array_init(res);
    if (asString) {
        for (int i = 0; i < strlen(info); i++)
            add_next_index_string(res, GramName(static_cast<unsigned char>(info[i])));
    } else {
        for (int i = 0; i < strlen(info); i++)
            add_next_index_long(res, static_cast<unsigned char>(info[i]));
    }
    return res;
}

inline zval* FlexGramInfoToZval(char** info, int num, int asString)
{
    zval *res = (zval *)safe_emalloc(1, sizeof(zval), 0);
    array_init(res);
    for (int i = 0; i < num; i++)
        add_next_index_zval(res, GramInfoToZval(info[i], asString));
    return res;
}

MystemAnalysesHandle* MystemAnalyzeUTF8(const char* str, int len)
{
    UnicodeString ucs_word = UnicodeString::fromUTF8(StringPiece(str, len));
    TSymbol *tsym_word = UnicodeToSymbols(ucs_word);
    MystemAnalysesHandle* res = MystemAnalyze(tsym_word, ucs_word.length());
    efree(tsym_word);
    return res;
}

void AddLemmaInfo(zval* array, MystemLemmaHandle* lemma, int gramInfoAsString)
{
    add_assoc_zval(array, "lemma", SymbolsToZval(MystemLemmaText(lemma), MystemLemmaTextLen(lemma)));
    add_assoc_zval(array, "form", SymbolsToZval(MystemLemmaForm(lemma), MystemLemmaFormLen(lemma)));
    add_assoc_long(array, "quality", MystemLemmaQuality(lemma));
    add_assoc_zval(array, "stem_gram", GramInfoToZval(MystemLemmaStemGram(lemma), gramInfoAsString));
    add_assoc_zval(array, "flex_gram", FlexGramInfoToZval(MystemLemmaFlexGram(lemma), MystemLemmaFlexGramNum(lemma), gramInfoAsString));
    add_assoc_long(array, "flex_len", MystemLemmaFlexLen(lemma));
    add_assoc_long(array, "rule_id", MystemLemmaRuleId(lemma));
}

void AddWordFormInfo(zval* array, MystemFormHandle* form, int gramInfoAsString)
{
    add_assoc_zval(array, "form", SymbolsToZval(MystemFormText(form), MystemFormTextLen(form)));
    add_assoc_zval(array, "stem_gram", GramInfoToZval(MystemFormStemGram(form), gramInfoAsString));
    add_assoc_zval(array, "flex_gram", FlexGramInfoToZval(MystemFormFlexGram(form), MystemFormFlexGramNum(form), gramInfoAsString));
}

void AddLemmaForms(zval* array, MystemLemmaHandle* lemma, int gramInfoAsString)
{
    MystemFormsHandle* forms = MystemGenerate(lemma);
    int forms_count = MystemFormsCount(forms);
    zval res;
    array_init(&res);
    for (int i = 0; i < forms_count; i++) {
        zval info;
        array_init(&info);
        AddWordFormInfo(&info, MystemForm(forms, i), gramInfoAsString);
        add_next_index_zval(&res, &info);
    }
    MystemDeleteForms(forms);
    add_assoc_zval(array, "form_list", &res);
}

/* If you declare any globals in php_mystem.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mystem)
*/

/* True global resources - no need for thread safety here */
static int le_mystem;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mystem.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mystem_globals, mystem_globals)
    STD_PHP_INI_ENTRY("mystem.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mystem_globals, mystem_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ proto array lemma(string word)
   Return lemma text */
PHP_FUNCTION(lemma)
{
    char *word = NULL;
    size_t word_len;
    zval res;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &word, &word_len) == FAILURE) {
        return;
    }

    MystemAnalysesHandle *analyses = MystemAnalyzeUTF8(word, word_len);
    int analyses_count = MystemAnalysesCount(analyses);

    array_init(&res);

    for (int i = 0; i < analyses_count; i++) {
        MystemLemmaHandle *lemma = MystemLemma(analyses, i);
        add_next_index_zval(&res, SymbolsToZval(MystemLemmaText(lemma), MystemLemmaTextLen(lemma)));
    }
    MystemDeleteAnalyses(analyses);
    RETURN_ZVAL(&res, 0, 0);
}
/* }}} */


/* {{{ proto array form_info(string word, bool gram_info_as_string)
   Return word form info */
PHP_FUNCTION(form_info)
{
    char *word = NULL;
    size_t word_len;
    int gram_info_as_string = 0;
    zval res;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|b", &word, &word_len, &gram_info_as_string) == FAILURE) {
        return;
    }

    MystemAnalysesHandle *analyses = MystemAnalyzeUTF8(word, word_len);
    int analyses_count = MystemAnalysesCount(analyses);

    array_init(&res);

    for (int i = 0; i < analyses_count; i++) {
        zval info;
        array_init(&info);
        MystemLemmaHandle *lemma = MystemLemma(analyses, i);
        AddLemmaInfo(&info, lemma, gram_info_as_string);
        add_next_index_zval(&res, &info);
    }
    MystemDeleteAnalyses(analyses);
    RETURN_ZVAL(&res, 0, 0);
}
/* }}} */

/* {{{ proto array generate_forms(string word, bool gram_info_as_string)
   Return word forms */
PHP_FUNCTION(generate_forms)
{
    char *word = NULL;
    size_t word_len;
    int gram_info_as_string = 0;
    zval res;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|b", &word, &word_len, &gram_info_as_string) == FAILURE) {
        return;
    }

    MystemAnalysesHandle *analyses = MystemAnalyzeUTF8(word, word_len);
    int analyses_count = MystemAnalysesCount(analyses);

    array_init(&res);

    for (int i = 0; i < analyses_count; i++) {
        zval info;
        array_init(&info);
        MystemLemmaHandle *lemma = MystemLemma(analyses, i);
        AddLemmaInfo(&info, lemma, gram_info_as_string);
        AddLemmaForms(&info, lemma, gram_info_as_string);
        add_next_index_zval(&res, &info);
    }
    MystemDeleteAnalyses(analyses);
    RETURN_ZVAL(&res, 0, 0);
}
/* }}} */

/* {{{ proto array gram_name(int value)
   Return grammar label name */
PHP_FUNCTION(gram_name)
{
    zend_long value;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &value) == FAILURE) {
        return;
    }

    RETURN_STRING(GramName(value));
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mystem)
{
    MYSTEM_GRAM_CONST("Before",           126);
    MYSTEM_GRAM_CONST("Postposition",     127);
    MYSTEM_GRAM_CONST("Adjective",        128);
    MYSTEM_GRAM_CONST("Adverb",           129);
    MYSTEM_GRAM_CONST("Composite",        130);
    MYSTEM_GRAM_CONST("Conjunction",      131);
    MYSTEM_GRAM_CONST("Interjunction",    132);
    MYSTEM_GRAM_CONST("Numeral",          133);
    MYSTEM_GRAM_CONST("Particle",         134);
    MYSTEM_GRAM_CONST("Preposition",      135);
    MYSTEM_GRAM_CONST("Substantive",      136);
    MYSTEM_GRAM_CONST("Verb",             137);
    MYSTEM_GRAM_CONST("AdjNumeral",       138);
    MYSTEM_GRAM_CONST("AdjPronoun",       139);
    MYSTEM_GRAM_CONST("AdvPronoun",       140);
    MYSTEM_GRAM_CONST("SubstPronoun",     141);
    MYSTEM_GRAM_CONST("Article",          142);
    MYSTEM_GRAM_CONST("PartOfIdiom",      143);
    MYSTEM_GRAM_CONST("Reserved",         144);
    MYSTEM_GRAM_CONST("Abbreviation",     145);
    MYSTEM_GRAM_CONST("IrregularStem",    146);
    MYSTEM_GRAM_CONST("Informal",         147);
    MYSTEM_GRAM_CONST("Distort",          148);
    MYSTEM_GRAM_CONST("Contracted",       149);
    MYSTEM_GRAM_CONST("Obscene",          150);
    MYSTEM_GRAM_CONST("Rare",             151);
    MYSTEM_GRAM_CONST("Awkward",          152);
    MYSTEM_GRAM_CONST("Obsolete",         153);
    MYSTEM_GRAM_CONST("SubstAdjective",   154);
    MYSTEM_GRAM_CONST("FirstName",        155);
    MYSTEM_GRAM_CONST("Surname",          156);
    MYSTEM_GRAM_CONST("Patr",             157);
    MYSTEM_GRAM_CONST("Geo",              158);
    MYSTEM_GRAM_CONST("Proper",           159);
    MYSTEM_GRAM_CONST("Present",          160);
    MYSTEM_GRAM_CONST("Notpast",          161);
    MYSTEM_GRAM_CONST("Past",             162);
    MYSTEM_GRAM_CONST("Future",           163);
    MYSTEM_GRAM_CONST("Past2",            164);
    MYSTEM_GRAM_CONST("Nominative",       165);
    MYSTEM_GRAM_CONST("Genitive",         166);
    MYSTEM_GRAM_CONST("Dative",           167);
    MYSTEM_GRAM_CONST("Accusative",       168);
    MYSTEM_GRAM_CONST("Instrumental",     169);
    MYSTEM_GRAM_CONST("Ablative",         170);
    MYSTEM_GRAM_CONST("Partitive",        171);
    MYSTEM_GRAM_CONST("Locative",         172);
    MYSTEM_GRAM_CONST("Vocative",         173);
    MYSTEM_GRAM_CONST("Singular",         174);
    MYSTEM_GRAM_CONST("Plural",           175);
    MYSTEM_GRAM_CONST("Gerund",           176);
    MYSTEM_GRAM_CONST("Infinitive",       177);
    MYSTEM_GRAM_CONST("Participle",       178);
    MYSTEM_GRAM_CONST("Indicative",       179);
    MYSTEM_GRAM_CONST("Imperative",       180);
    MYSTEM_GRAM_CONST("Conditional",      181);
    MYSTEM_GRAM_CONST("Subjunctive",      182);
    MYSTEM_GRAM_CONST("Short",            183);
    MYSTEM_GRAM_CONST("Full",             184);
    MYSTEM_GRAM_CONST("Superlative",      185);
    MYSTEM_GRAM_CONST("Comparative",      186);
    MYSTEM_GRAM_CONST("Possessive",       187);
    MYSTEM_GRAM_CONST("Person1",          188);
    MYSTEM_GRAM_CONST("Person2",          189);
    MYSTEM_GRAM_CONST("Person3",          190);
    MYSTEM_GRAM_CONST("Feminine",         191);
    MYSTEM_GRAM_CONST("Masculine",        192);
    MYSTEM_GRAM_CONST("Neuter",           193);
    MYSTEM_GRAM_CONST("MasFem",           194);
    MYSTEM_GRAM_CONST("Perfect",          195);
    MYSTEM_GRAM_CONST("Imperfect",        196);
    MYSTEM_GRAM_CONST("Passive",          197);
    MYSTEM_GRAM_CONST("Active",           198);
    MYSTEM_GRAM_CONST("Reflexive",        199);
    MYSTEM_GRAM_CONST("Impersonal",       200);
    MYSTEM_GRAM_CONST("Animated",         201);
    MYSTEM_GRAM_CONST("Inanimated",       202);
    MYSTEM_GRAM_CONST("Praedic",          203);
    MYSTEM_GRAM_CONST("Parenth",          204);
    MYSTEM_GRAM_CONST("Transitive",       205);
    MYSTEM_GRAM_CONST("Intransitive",     206);
    MYSTEM_GRAM_CONST("Definite",         207);
    MYSTEM_GRAM_CONST("Indefinite",       208);
    MYSTEM_GRAM_CONST("SimConj",          209);
    MYSTEM_GRAM_CONST("SubConj",          210);
    MYSTEM_GRAM_CONST("PronounConj",      211);
    MYSTEM_GRAM_CONST("CorrelateConj",    212);
    MYSTEM_GRAM_CONST("AuxVerb",          213);
    MYSTEM_GRAM_CONST("Dual",             214);
    MYSTEM_GRAM_CONST("Poss1p",           215);
    MYSTEM_GRAM_CONST("Poss1pSg",         216);
    MYSTEM_GRAM_CONST("Poss1pPl",         217);
    MYSTEM_GRAM_CONST("Poss2p",           218);
    MYSTEM_GRAM_CONST("Poss2pSg",         219);
    MYSTEM_GRAM_CONST("Poss2pPl",         220);
    MYSTEM_GRAM_CONST("Poss3p",           221);
    MYSTEM_GRAM_CONST("Poss3pSg",         222);
    MYSTEM_GRAM_CONST("Poss3pPl",         223);
    MYSTEM_GRAM_CONST("Predic1pSg",       224);
    MYSTEM_GRAM_CONST("Predic1pPl",       225);
    MYSTEM_GRAM_CONST("Predic2pSg",       226);
    MYSTEM_GRAM_CONST("Predic2pPl",       227);
    MYSTEM_GRAM_CONST("Predic3pSg",       228);
    MYSTEM_GRAM_CONST("Predic3pPl",       229);
    MYSTEM_GRAM_CONST("Elative",          230);
    MYSTEM_GRAM_CONST("DerivedAdjective", 231);
    MYSTEM_GRAM_CONST("Evidential",       232);
    MYSTEM_GRAM_CONST("Negated",          233);
    MYSTEM_GRAM_CONST("Potential",        234);
    MYSTEM_GRAM_CONST("Medial",           235);
    MYSTEM_GRAM_CONST("Human",            236);
    MYSTEM_GRAM_CONST("AssocPlural",      237);
    MYSTEM_GRAM_CONST("Optative",         238);
    MYSTEM_GRAM_CONST("Converb",          239);
    MYSTEM_GRAM_CONST("Simultaneous",     240);
    MYSTEM_GRAM_CONST("Connegative",      241);
    MYSTEM_GRAM_CONST("Resultative",      242);
    MYSTEM_GRAM_CONST("Subjective",       243);
    MYSTEM_GRAM_CONST("Count",            244);
    MYSTEM_GRAM_CONST("GoodForm",         245);
    MYSTEM_GRAM_CONST("PredicPoss",       246);
    MYSTEM_GRAM_CONST("Intention",        247);
    MYSTEM_GRAM_CONST("Honorific",        248);
    MYSTEM_GRAM_CONST("Equative",         249);
    MYSTEM_GRAM_CONST("Predic",           250);
    MYSTEM_GRAM_CONST("Obligatory",       251);
    MYSTEM_GRAM_CONST("Max",              252);

    MYSTEM_QUAL_CONST("Dictionary",  0);
    MYSTEM_QUAL_CONST("Bastard",     1);
    MYSTEM_QUAL_CONST("Sob",         2);
    MYSTEM_QUAL_CONST("Prefixoid",   4);
    MYSTEM_QUAL_CONST("Foundling",   8);
    MYSTEM_QUAL_CONST("BadRequest",  16);
    MYSTEM_QUAL_CONST("FromEnglish", 65536);
    MYSTEM_QUAL_CONST("ToEnglish",   131072);
    MYSTEM_QUAL_CONST("Untranslit",  262144);
    MYSTEM_QUAL_CONST("Overrode",    1048576);
    MYSTEM_QUAL_CONST("Fix",         16777216);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mystem)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mystem)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "mystem support", "enabled");
    php_info_print_table_end();
}
/* }}} */

/* {{{ mystem_functions[]
 *
 * Every user visible function must have an entry in mystem_functions[].
 */
const zend_function_entry mystem_functions[] = {
    ZEND_NS_FE(MYSTEM_NS, lemma,          NULL)
    ZEND_NS_FE(MYSTEM_NS, form_info,      NULL)
    ZEND_NS_FE(MYSTEM_NS, generate_forms, NULL)
    ZEND_NS_FE(MYSTEM_NS, gram_name,      NULL)
    PHP_FE_END    /* Must be the last line in mystem_functions[] */
};
/* }}} */

/* {{{ mystem_module_entry
 */
zend_module_entry mystem_module_entry = {
    STANDARD_MODULE_HEADER,
    "mystem",
    mystem_functions,
    PHP_MINIT(mystem),
    PHP_MSHUTDOWN(mystem),
    NULL,
    NULL,
    PHP_MINFO(mystem),
    PHP_MYSTEM_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYSTEM
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(mystem)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
