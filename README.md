# Poštovní server

**Hodnocení**: 5.0 bodů (MAXIMÁLNĚ 8.64, POKUD V PROGTESTU VIDÍTE VÍCE BODŮ, JE TO VČETNĚ VČASNÉHO ODEVZDÁNÍ, KTERÉ SE DO TĚCHTO STATISTIK NEUVÁDÍ, DĚKUJI.)  
**Termín odevzdání**: 17.04.2023 11:59:59

## Zadání

Úkolem je realizovat třídu `CMailServer`, která bude simulovat činnost jednoduchého poštovního serveru.

Předpokládáme, že server zprostředkovává zasílání e-mailů uvnitř organizace. Každý e-mail je reprezentován instancí třídy `CMail`, obsahuje adresu odesílatele, adresu příjemce a tělo zprávy (vše jsou řetězce). Mail server umí zprávu odeslat a zjišťovat obsah odeslané a přijaté pošty (outbox a inbox) pro jednotlivé e-mailové adresy. Seznam odeslané a přijaté pošty je poskytnut pro jednotlivé e-mailové adresy pomocí iterátoru, který umožní iteraci po jednotlivých mailech.

Vlastní třída `CMailServer` musí správně zvládat kopírování, aby její kopie mohly sloužit pro archivační a auditní účely.

### Povinné části:

#### Třída `CMail`

- **Konstruktor** (`from`, `to`, `body`)
  - Vytvoří instanci e-mailu se složkami `from`, `to` a `body` vyplněnými podle parametrů.
  
- **Operátor `==`**
  - Porovná obsah dvou instancí `CMail`. Vrací `true`, pokud jsou všechny složky shodné.

- **Operátor `<<`**
  - Zobrazí informace o mailu do zadaného streamu.

#### Třída `CMailServer`

- **Implicitní konstruktor**
  - Vytvoří prázdnou instanci serveru.

- **Destruktor**
  - Uvolní prostředky alokované instancí.

- **Kopírující konstruktor, operátor `=`**
  - Vytvoří identické kopie instance podle standardních pravidel.

- **`sendMail(mail)`**
  - Zašle e-mail předaný v parametrech a zařadí ho do odpovídajících schránek odesílatele a příjemce. Schránka se automaticky vytvoří po zpracování prvního e-mailu.

- **`outbox(email)`**
  - Zpřístupní poštu odeslanou ze zadané adresy pomocí iterátoru.

- **`inbox(email)`**
  - Zpřístupní poštu přijatou na zadanou adresu pomocí iterátoru.

#### Třída `CMailIterator`

- **Operátor `bool`**
  - Zjistí, zda iterátor odkazuje na platný e-mail (vrací `true`), nebo zda dosáhl konce seznamu (`false`).

- **Operátor `*`**
  - Zpřístupní e-mail na aktuální pozici iterátoru.

- **Operátor `++`**
  - Přesune iterátor na další e-mail v seznamu.

### Nepovinné části:

Pro optimalizaci výkonu je možné v nepovinné části řešení implementovat rychlejší vyhledávání adres a optimalizaci kopírování a ukládání e-mailů.

---

Tento kód musí splňovat veřejné rozhraní podle ukázky. Pokud řešení nebude odpovídat, může dojít k chybě při kompilaci. Soubor s řešením nesmí obsahovat hlavičkové soubory a funkci `main`. Funkce `main` může zůstat, ale pouze obalená direktivami podmíněného překladu.

