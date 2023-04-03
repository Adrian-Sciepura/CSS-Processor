#include "Processor.h"

Processor::Processor()
{
    this->lastSection = nullptr;
    this->prevAttributeName = " ";

    this->readMode = false;
    this->wasPreviousElementAttributeName = false;
    this->isInSection = false;
    this->foundBracket = false;
    this->foundColon = false;
    this->gotAllSelectors = false;
}

Processor::~Processor()
{

}

void Processor::start()
{
    char c;
    char buffer[1000];
    int counter = 0;
    bool endOfLine = false;
    bool flag = false;

    while (c = getchar())
    {
        if (flag)
            break;

        if(!readMode)
        {
            switch (c)
            {
                case '\t':
                    continue;
                case ' ':
                {
                    if (counter == 0)
                        continue;
                    else if (!this->wasPreviousElementAttributeName && this->gotAllSelectors)
                        endOfLine = true;
                    break;
                }
                case '{':
                case '}':
                {
                    this->foundBracket = true;
                    endOfLine = true;
                    break;
                }
                case ':':
                {
                    if (this->gotAllSelectors)
                    {
                        this->foundColon = true;
                        endOfLine = true;
                    }
                    break;
                }
                case ',':
                {
                    if (!this->wasPreviousElementAttributeName)
                        endOfLine = true;

                    break;
                }
                case '\n':
                {
                    if (counter == 0)
                        continue;
                    else
                        endOfLine = true;
                }
                case ';':
                {
                    if(this->gotAllSelectors)
                        endOfLine = true;
                    break;
                }
            }
        }
        else
        {
            if (c == '\n')
            {
                if (counter == 0)
                    continue;
                endOfLine = true;
            }
        }

        if (c == '\xff')
        {
            flag = true;
            if (counter == 0)
                continue;
            endOfLine = true;
        }

        if (endOfLine)
        {
            buffer[counter] = '\0';
            counter++;

            for (int i = counter - 2; i >= 0; i--)
                if (buffer[i] <= ' ')
                    buffer[i] = '\0';
                else
                    break;


            if (checkExtra(buffer))
                this->readMode = !this->readMode;
            else
            {
                if (readMode)
                    interpretCommand(buffer);
                else
                    interpretCSS(buffer, counter-1);
            }

            counter = 0;
            endOfLine = false;
            continue;
        }


        buffer[counter] = c;
        counter++;
    }
}

bool Processor::checkExtra(const char* text)
{
    if (strcmp(text, "****") == 0 || strcmp(text, "????") == 0)
        return true;

    return false;
}

void Processor::printResult(char* arg1, char& action, char* arg2)
{
    std::cout << arg1 << ',' << action << ',' << arg2 << " == ";
}

void Processor::interpretCSS(char* text, int length)
{
    if (!this->isInSection)
    {
        this->lastSection = this->list.newSection();
        this->isInSection = true;
    }

    if (!this->gotAllSelectors)
    {
        if (this->foundBracket)
        {
            this->gotAllSelectors = true;
            this->foundBracket = false;
        }

        if (*text != '\0')
            this->lastSection->selectors.add({ text });
    }
    else
    {
        if (this->foundColon)
        {
            this->prevAttributeName = text;
            this->foundColon = false;
            this->wasPreviousElementAttributeName = true;
        }
        else if(*text != '\0')
        {
            this->lastSection->attributes.add({ this->prevAttributeName, text });
            this->wasPreviousElementAttributeName = false;
        }

        if (this->foundBracket)
        {
            this->isInSection = false;
            this->gotAllSelectors = false;
            this->foundBracket = false;
        }
    }
}

void Processor::interpretCommand(char* text)
{
    if (*text == '\0' || *text == ' ')
        return;

    if (strcmp(text, "?") == 0)
    {
        std::cout << "? == " << this->list.numberOfSections << '\n';
    }
    else if (strcmp(text, ">") == 0)
    {
        ListNode* node = this->list.first;
        while (node != nullptr)
        {
            for (int i = 0; i < node->cursor; i++)
            {
                if (node->sections[i] != nullptr)
                {
                    node->sections[i]->print();
                }
            }
            node = node->next;
        }
    }
    else
    {
        char* arg1;
        char action;
        char* arg2;

        char* search;
        search = strchr(text, ',');
        *search = '\0';
        arg1 = text;
        text = search + 1;

        search = strchr(text, ',');
        *search = '\0';
        action = *text;
        text = search + 1;
        arg2 = text;

        switch (action)
        {
            case 'S':
            {
                char *a1, *a2;
                int num1 = strtol(arg1, &a1, 10);
                int num2 = strtol(arg2, &a2, 10);
                if (*a1 == NULL && *a2 == NULL)
                {
                    Section* section = this->list[num1 - 1];
                    if (section == nullptr)
                        break;

                    ForwardListNode<String>* selector = section->selectors.find(num2 - 1);
                    if (selector == nullptr)
                        break;

                    this->printResult(arg1, action, arg2);
                    std::cout << selector->data << '\n';
                }
                else if (*a1 == NULL)
                {
                    Section* section = this->list[num1 - 1];
                    if (section == nullptr)
                        break;

                    this->printResult(arg1, action, arg2);
                    std::cout << section->selectors.numberOfNodes << '\n';
                }
                else
                {
                    int result = this->list.countSelectorOccurrences({ arg1 });
                    this->printResult(arg1, action, arg2);
                    std::cout << result << '\n';                  
                }
                break;
            }
            case 'A':
            {
                char* a1;
                int num1 = strtol(arg1, &a1, 10);
                if (*a1 == NULL)
                {
                    Section* section = this->list[num1 - 1];
                    if (section == nullptr)
                        break;

                    if (arg2[0] == '?')
                    {
                        this->printResult(arg1, action, arg2);
                        std::cout << section->attributes.numberOfNodes << '\n';
                    }
                    else
                    {
                        ForwardListNode<Attribute>* attribute = section->attributes.find({ arg2, "" });
                        if (attribute == nullptr)
                            break;

                        this->printResult(arg1, action, arg2);
                        std::cout << attribute->data.value << '\n';
                    }
                }
                else
                {
                    int result = this->list.countAttributeOccurrences({ arg1 });
                    this->printResult(arg1, action, arg2);
                    std::cout << result << '\n';
                }
                break;
            }
            case 'E':
            {
                ListNode* node = this->list.last;
                ForwardListNode<String>* searchForSelector = nullptr;
                ForwardListNode<Attribute>* searchForAttribute = nullptr;
                while (node != nullptr)
                {
                    for (int i = node->cursor - 1; i >= 0; i--)
                    {
                        if (node->sections[i] == nullptr)
                            continue;

                        searchForSelector = node->sections[i]->selectors.find(arg1);
                        if (searchForSelector == nullptr)
                            continue;

                        searchForAttribute = node->sections[i]->attributes.find({ arg2, "" });
                        if (searchForAttribute == nullptr)
                            continue;

                        this->printResult(arg1, action, arg2);
                        std::cout << searchForAttribute->data.value << '\n';
                        return;
                    }
                    node = node->previous;
                }
                break;
            }
            case 'D':
            {
                char* a1;
                int num1 = strtol(arg1, &a1, 10);
                if (*a1 == NULL)
                {
                    if (arg2[0] == '*')
                    {
                        if (this->list.removeSection(num1 - 1))
                        {
                            this->printResult(arg1, action, arg2);
                            std::cout << "deleted\n";
                        }
                    }
                    else
                    {
                        Section* section = this->list[num1 - 1];
                        if (section == nullptr)
                            break;

                        if (!section->attributes.remove({ arg2, "" }))
                            break;

                        if (section->attributes.numberOfNodes == 0)
                            this->list.removeSection(num1 - 1);
                        
                        this->printResult(arg1, action, arg2);
                        std::cout << "deleted\n";
                    }
                }
                break;
            }
        }
    }
}
