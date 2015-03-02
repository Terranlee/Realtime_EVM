#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <QString>

namespace error
{
    class MessageError
	{
    protected:
        QString message;
    public:
        MessageError(QString m) : message(m) {}
        virtual QString print() { return message; }
	};

    struct NoFaceError : public MessageError
    {
    public:
        NoFaceError(QString m = "No Face Detected") : MessageError(m) {}
    };

    //errors related to numbers
    class NumberError
    {
    protected:
        QString which;        //which arg is it?
        float args;           //what is the arg?
    public:
        NumberError(QString w , float a ) : which(w) , args(a) {}
        virtual QString print_message() = 0;
    };

    //when some parameters are negative , public derived from NumberError
    class NegativeError : public NumberError
    {
    public:
        NegativeError(QString w , float a) : NumberError(w , a) {}
        virtual QString print_message(){
            return QString("number ") + QString("%1").arg(args) + QString(" of ") + which + QString(" is negative");
        }
    };

    //when some parameters are too large
    class TooLargeError : public NumberError
    {
    public:
        TooLargeError(QString w , float a) : NumberError(w , a) {}
        virtual QString print_message(){
            return QString("number ") + QString("%1").arg(args) + QString(" of ") + which + QString(" is too large");
        }
    };

    //when some parameters are too small
    class TooSmallError : public NumberError
    {
    public:
        TooSmallError(QString w , float a) : NumberError(w , a) {}
        virtual QString print_message(){
            return QString("number ") + QString("%1").arg(args) + QString(" of ") + which + QString(" is too small");
        }
    };
}

#endif // ERROR_H
