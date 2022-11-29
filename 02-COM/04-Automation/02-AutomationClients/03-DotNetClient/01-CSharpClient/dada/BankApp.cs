using System;
using NUnit.Framework;

namespace BankApp
{
    public class BankAccount
    {
        private decimal amtbalance;
        private decimal minimumBalance = 20m;

        public void bankDeposit(decimal amount)
        {
            amtbalance += amount;
        }

        public void Withdraw(decimal amount)
        {
            amtbalance -= amount;
        }

        public void TransferFunds(BankAccount destination, decimal amount)
        {
            if (amtbalance - amount < minimumBalance)
                throw new InsufficientFundsException();

            destination.bankDeposit(amount);

            Withdraw(amount);
        }

        public decimal AmountBalance
        {
            get { return amtbalance; }
        }

        public decimal MinBalance
        {
            get { return minimumBalance; }
        }
    }

    public class InsufficientFundsException : ApplicationException
    {

    }

    [TestFixture]
    public class BankAccountTest
    {
        BankAccount source;
        BankAccount destination;

        [Setup]
        public void Init()
        {
            source = new BankAccount();
            source.bankDeposit(300m); 
        }
    }
}