
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
#define MYSTEM_GRAMINFO_NS "Mystem\\GramInfo"
#define MYSTEM_QUAL_CONST(NAME, VALUE) REGISTER_NS_LONG_CONSTANT("Mystem\\QualityFlags", NAME, VALUE, CONST_CS | CONST_PERSISTENT);

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
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Before",           126, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Postposition",     127, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Adjective",        128, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Adverb",           129, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Composite",        130, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Conjunction",      131, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Interjunction",    132, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Numeral",          133, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Particle",         134, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Preposition",      135, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Substantive",      136, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Verb",             137, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "AdjNumeral",       138, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "AdjPronoun",       139, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "AdvPronoun",       140, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "SubstPronoun",     141, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Article",          142, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "PartOfIdiom",      143, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Reserved",         144, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Abbreviation",     145, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "IrregularStem",    146, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Informal",         147, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Distort",          148, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Contracted",       149, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Obscene",          150, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Rare",             151, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Awkward",          152, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Obsolete",         153, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "SubstAdjective",   154, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "FirstName",        155, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Surname",          156, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Patr",             157, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Geo",              158, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Proper",           159, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Present",          160, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Notpast",          161, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Past",             162, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Future",           163, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Past2",            164, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Nominative",       165, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Genitive",         166, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Dative",           167, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Accusative",       168, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Instrumental",     169, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Ablative",         170, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Partitive",        171, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Locative",         172, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Vocative",         173, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Singular",         174, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Plural",           175, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Gerund",           176, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Infinitive",       177, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Participle",       178, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Indicative",       179, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Imperative",       180, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Conditional",      181, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Subjunctive",      182, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Short",            183, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Full",             184, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Superlative",      185, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Comparative",      186, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Possessive",       187, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Person1",          188, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Person2",          189, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Person3",          190, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Feminine",         191, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Masculine",        192, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Neuter",           193, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "MasFem",           194, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Perfect",          195, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Imperfect",        196, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Passive",          197, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Active",           198, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Reflexive",        199, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Impersonal",       200, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Animated",         201, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Inanimated",       202, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Praedic",          203, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Parenth",          204, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Transitive",       205, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Intransitive",     206, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Definite",         207, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Indefinite",       208, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "SimConj",          209, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "SubConj",          210, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "PronounConj",      211, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "CorrelateConj",    212, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "AuxVerb",          213, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Dual",             214, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss1p",           215, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss1pSg",         216, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss1pPl",         217, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss2p",           218, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss2pSg",         219, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss2pPl",         220, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss3p",           221, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss3pSg",         222, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Poss3pPl",         223, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic1pSg",       224, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic1pPl",       225, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic2pSg",       226, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic2pPl",       227, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic3pSg",       228, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic3pPl",       229, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Elative",          230, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "DerivedAdjective", 231, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Evidential",       232, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Negated",          233, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Potential",        234, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Medial",           235, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Human",            236, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "AssocPlural",      237, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Optative",         238, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Converb",          239, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Simultaneous",     240, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Connegative",      241, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Resultative",      242, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Subjective",       243, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Count",            244, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "GoodForm",         245, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "PredicPoss",       246, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Intention",        247, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Honorific",        248, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Equative",         249, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Predic",           250, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Obligatory",       251, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(MYSTEM_GRAMINFO_NS, "Max",              252, CONST_CS | CONST_PERSISTENT);

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
