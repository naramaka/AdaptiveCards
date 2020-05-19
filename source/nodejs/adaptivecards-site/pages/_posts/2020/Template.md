---
title: Template
subtitle: Introduction to new template syntax and Adaptive Expression Language usage
date: 2020-04-27
github_username: jwoo-msft
---
# Template
I will show you how to use the basic template features and some advanced ones. Along the way, I will also show you our updated template syntax, and introduce Adaptive Expression Language. We will be working on a Expense report card. This expense report card is available in [our github repository](https://github.com/microsoft/AdaptiveCards/blob/master/samples/v1.2/Scenarios/ExpenseReport.json). We will turn this AdaptiveCards into a templated AdaptiveCards, so we can dynamically update AdaptiveCards based on data.

![Expense Report First Iteration](Template/ExpenseReport01.png)

## Data Binding
The expense report's json is over 800 lines. To update the contents of the card, we could update it by editing Adaptive Elements objects. Since template is a new way to update AdaptiveCards, we will update the content using template.
 
As an example, if we want to change the name of Submitter, **Matt Hidinger** to **Jopseh Woo**. 
Given the json below, we will update it with template
```json
{
    "type": "FactSet",
    "spacing": "Large",
    "facts": [
        {
            "title": "Submitted By",
            "value": "**Matt Hidinger**  matt@contoso.com"
        },
        ...
```

```json
{
    "type": "FactSet",
    "spacing": "Large",
    "facts": [
        {
            "title": "Submitted By",
            "value": "**${submitter.name}**  ${submitter.e-mail}"
        },
        ...
```

The example above misses data. To use template, we have to provide data.  Data can be any valid json

```json
{
    "submitter" :
    { 
        "name" : "Joseph Woo",
        "e-mail" : "hello@world.com"
    }

}
```

Updated card

![Expense Report First Iteration](Template/ExpenseReport02.png)

As long as data's format doesn't change, this AdaptiveCards can be re-used. AdaptiveCards will be updated according to the data the card is bound to. Template can also be used in repeating a layout.
Expense Report Card has following layout, each row for expense item has the same layout.

![Expense Report First Iteration](Template/ExpenseReport03.png)

Without template, we have to define each layout for each expense items. Since there are three expense items, we have to have three ColumnSet each defining the items.

```json
{
    "type": "ColumnSet",
    "columns": [
        {
            "type": "Column",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "06/19",
                    "wrap": true
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "spacing": "Medium",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Air Travel Expense",
                    "wrap": true
                }
            ],
            "width": "stretch"
        },
        {
            "type": "Column",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "$ 300",
                    "wrap": true
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "id": "chevronDown1",
            "spacing": "Small",
            "verticalContentAlignment": "Center",
            "items": [
                {
                    "type": "Image",
                    "selectAction": {
                        "type": "Action.ToggleVisibility",
                        "title": "collapse",
                        "targetElements": [
                            "cardContent1",
                            "chevronUp1",
                            "chevronDown1"
                        ]
                    },
                    "url": "https://adaptivecards.io/content/down.png",
                    "width": "20px",
                    "altText": "collapsed"
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "id": "chevronUp1",
            "isVisible": false,
            "spacing": "Small",
            "verticalContentAlignment": "Center",
            "items": [
                {
                    "type": "Image",
                    "selectAction": {
                        "type": "Action.ToggleVisibility",
                        "title": "expand",
                        "targetElements": [
                            "cardContent1",
                            "chevronUp1",
                            "chevronDown1"
                        ]
                    },
                    "url": "https://adaptivecards.io/content/up.png",
                    "width": "20px",
                    "altText": "expanded"
                }
            ],
            "width": "auto"
        }
    ]
}
```
To use template we will do followings
1. We keep one layout of expense item for template, and remove all other layouts of the expense items.
2. We format the layout with the template
3. We provide data that the template expects

```json
{
    "$data" : "${expense}",
    "type": "ColumnSet",
    "columns": [
        {
            "type": "Column",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "${date}",
                    "wrap": true
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "spacing": "Medium",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "${description}",
                    "wrap": true
                }
            ],
            "width": "stretch"
        },
        {
            "type": "Column",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "$${amount}",
                    "wrap": true
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "id": "chevronDown1",
            "spacing": "Small",
            "verticalContentAlignment": "Center",
            "items": [
                {
                    "type": "Image",
                    "selectAction": {
                        "type": "Action.ToggleVisibility",
                        "title": "collapse",
                        "targetElements": [
                            "cardContent1",
                            "chevronUp1",
                            "chevronDown1"
                        ]
                    },
                    "url": "https://adaptivecards.io/content/down.png",
                    "width": "20px",
                    "altText": "collapsed"
                }
            ],
            "width": "auto"
        },
        {
            "type": "Column",
            "id": "chevronUp1",
            "isVisible": false,
            "spacing": "Small",
            "verticalContentAlignment": "Center",
            "items": [
                {
                    "type": "Image",
                    "selectAction": {
                        "type": "Action.ToggleVisibility",
                        "title": "expand",
                        "targetElements": [
                            "cardContent1",
                            "chevronUp1",
                            "chevronDown1"
                        ]
                    },
                    "url": "https://adaptivecards.io/content/up.png",
                    "width": "20px",
                    "altText": "expanded"
                }
            ],
            "width": "auto"
        }
    ]
}
```

We've introduced new keyword [$data](https://docs.microsoft.com/en-us/adaptive-cards/templating/language#assigning-a-data-context-to-elements). $data is used in this example to specify data in our source data, and this chosen data is applied within the boundary of [a json object](https://www.w3schools.com/js/js_json_objects.asp) that the $data is defined. In addition, the data that was bound by $data will be applied to the json object's sub elemetns as well. For example, if $data context is defined in Container, and if TextBlock is a item of the Container, the TextBlock will get the same data context. 

The json pair shown below specifies that the ColumnSet will use ```expense``` in data binding. 

```json
{
    "$data" : "${expense}",
    "type": "ColumnSet",
    "columns": [
        {
            "type": "Column",
```

```json
"$data" : "${expense}"
```

This is our current data we designed

```json
{
    "submitter" :
    { 
        "name" : "Joseph Woo",
        "e-mail" : "hello@world.com"
    }

}
```

There is no entry with ```expense``` yet in our data. So let's add it. 

```json
{
    "submitter" :
    { 
        "name" : "Joseph Woo",
        "e-mail" : "hello@world.com"
    },
    "expense" :
    { 
        "date" : "12/24/2020",
        "amount" : 500,
        "description" : "Air Travel Expense" 
    }

}
```
With the addition of ```expense```, binding will occur almost correctly. Another powerful feature of template is repeating elements. As shown in the example, what was lacking was the ability to popluate layout per submitter's expense.

This can be accomplished by template's [repeating element feature](https://docs.microsoft.com/en-us/adaptive-cards/templating/language#repeating-items-in-an-array). This allows adaptive elements to be repeated by simply changing the data type to array. If array, the enclosing json object will be repeated by the number of elements in the array.

```json
{
    "submitter" :
    { 
        "name" : "Joseph Woo",
        "e-mail" : "hello@world.com"
    },
    "expenses" : [ 
        { 
            "date" : "12/24/2020",
            "amount" : 500,
            "description" : "Air Travel Expense" 
        },
        { 
            "date" : "12/22/2020",
            "amount" : 300,
            "description" : "Auto Mobile Expense" 
        },
        { 
            "date" : "12/21/2020",
            "amount" : 400,
            "description" : "Air Travel Expense" 
        },
        { 
            "date" : "12/19/2020",
            "amount" : 700,
            "description" : "Air Travel Expense" 
        }
    ]

}
```

There is one more problem. The type of ```amount``` is integer. This can be a problem. For example, if AdaptiveCards parser see this ```"text" : 500``` in  ```TextBlock``` after expansion. It will drop entire TextBlock, or text may be left empty because the parser expects string type.

To convert integer to string, we can use ```string``` functions. Template linbrary provides functions or expression through [Adpative Expression Language library](https://github.com/microsoft/BotBuilder-Samples/tree/master/experimental/common-expression-language). For the list of api, please see [here](https://github.com/microsoft/BotBuilder-Samples/blob/master/experimental/common-expression-language/prebuilt-functions.md). Changing ```"text": "$${amount}"``` to ```"text": "$${string(amount)}"``` resolves our final issue. Finally we don't need every entries of the ColumnSet for the expenses in Expese Report card, so we remove them. Don't forget that we changed entry ```expense``` to ```expenses``` in our data if you're following this example. If the temmplate is run in the designer, it will look like this.

![Expense Report First Iteration](Template/ExpenseReport04.png)

Expense Report card also has hidden element whose visibility can be toggled by interacting with cheveron mark. To generate this element dynamically, we will create a container that will include both ColumnSet for the expense items and the toggle visibility element, then bind the data to the new Container such that the new Container will get repeated.

```json
{
            "type" : "Container",
            "$data": "${expenses}",
            "items" : [       
            { // expense item with cheveron mark
                "type": "ColumnSet",
                "columns": [
            // skipped contents ...  
            { // hidden element with toggle visibility 
                "type": "Container",
                "id": "cardContent0",
                "isVisible": false,
                "items": [
                    {
```

Toggle Visibility works by targeting AdaptiveElement's id. Using the id, we can ask the AdaptiveElement with targeted id to toggle its visibility.
```json
 "selectAction": {
                    "type": "Action.ToggleVisibility",
                    "title": "show history",
                    "targetElements": [
                        "cardContent0",
                        "chevronUp0",
                        "chevronDown0"
                    ]
                }
```
```targetElements``` in the above example contains array of ids that the ```selectionAction``` is targetting.


If ```"id": "cardContent0",```  is static text, toggle Visibility won't work as designed. Since all of the repeated element's id would have same ids. We can use keyword ```$index``` for such cases. ```$index``` is current repeating element's index. For example, if ```"id": "cardContent${$index}",``` was part of 5th element in the array, $index will be evaluated to ```"id": "cardContent5",```. 
```json
{
    "type" : "Container",
    // expenses is json array, and will cause current Containeer including its sub elements to repeat for len(${expenses})
    "$data": "${expenses}",
    "items" : [       
    { // expense item with cheveron mark
        "type": "ColumnSet",
        "columns": [
    // skipped contents ...  
    { // hidden element with toggle visibility 
        "type": "Container",
        "id": "cardContent{$index}",
        "isVisible": false,
        "items": [
            {
```

Finally, total amount of expense shown below is static, and should be fixed

```json
"items": [
{
    "type": "TextBlock",
    "text": "404.30"
},
```

Using AEL [sum](https://github.com/microsoft/BotBuilder-Samples/blob/master/experimental/common-expression-language/prebuilt-functions.md#sum), [select](https://github.com/microsoft/BotBuilder-Samples/blob/master/experimental/common-expression-language/prebuilt-functions.md#select) functions, we modify "403.30" to ```${sum(select(expenses, x, x.amount))}```. This change will allow the card to dynamically update the expanses based on the data
```json
"items": [
{
    "type": "TextBlock",
    "text": "${string(sum(select(expenses, x, x.amount)))}"
},
```
After this changes, total sum correctly updated.

![Expense Report First Iteration](Template/ExpenseReport05.png)